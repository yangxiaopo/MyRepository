#!/bin/bash

jdk=jdk-7u79-linux-x64.tar.gz
jdk_tar_name=jdk1.7.0_79
jdk_install_path=/usr/lib/jvm
mysql_client=MySQL-client-5.5.51-1.el6.x86_64.rpm
mysql_server=MySQL-server-5.5.51-1.el6.x86_64.rpm
libevent=libevent-2.0.21-stable.tar.gz
libevent_name=${libevent%.tar.*}
memcached=memcached-1.4.29.tar.gz
memcached_name=${memcached%.tar.*}
tomcat=apache-tomcat-7.0.41.tar.gz
tomcat_name=${tomcat%.tar.*}

sed -i '1cLANG="en_US.UTF-8"' /etc/sysconfig/i18n

if [ "`rpm -qa|grep jdk`" != "" ]; then
	rpm -qa|grep jdk|xargs rpm -e --nodeps
	cp /etc/profile /etc/profile.bak
	sed -i 's/JAVA_HOME=\/usr\/lib\/jvm\/java7//' /etc/profile
	sed -i 's/JRE_HOME=\${JAVA_HOME}\/jre//' /etc/profile
	sed -i 's/CLASSPATH=.:\${JAVA_HOME}\/lib:\${JRE_HOME}\/lib//' /etc/profile
	sed -i 's/PATH=\${JAVA_HOME}\/bin:\$PATH//' /etc/profile
fi

rm -rf /usr/lib/jvm
mkdir -p /usr/lib/jvm
tar zxvf ${jdk} -C ${jdk_install_path}
mv ${jdk_install_path}/${jdk_tar_name} ${jdk_install_path}/java7
cp /etc/profile /etc/profile.bak
echo "export JAVA_HOME=/usr/lib/jvm/java7" >> /etc/profile
echo "export JRE_HOME=\${JAVA_HOME}/jre" >> /etc/profile
echo "export CLASSPATH=.:\${JAVA_HOME}/lib:\${JRE_HOME}/lib" >> /etc/profile
echo "export PATH=\${JAVA_HOME}/bin:\$PATH" >> /etc/profile
source /etc/profile
update-alternatives --install /usr/bin/java java /usr/lib/jvm/java7/bin/java 300 
update-alternatives --install /usr/bin/javac javac /usr/lib/jvm/java7/bin/javac 300 
update-alternatives --install /usr/bin/jar jar /usr/lib/jvm/java7/bin/jar 300 
update-alternatives --install /usr/bin/javah javah /usr/lib/jvm/java7/bin/javah 300 
update-alternatives --install /usr/bin/javap javap /usr/lib/jvm/java7/bin/javap 300
update-alternatives --config java ${jdk_install_path}/java7/bin/java
java -version

if [ "`rpm -qa|grep -i mysql`" != "" ]; then
	ps -ef | grep mysql | grep -v grep |awk '{print $2}'| xargs kill -9
	rpm -qa|grep -i mysql|xargs rpm -e --nodeps
fi

rm -fr /usr/lib/mysql
rm -fr /usr/include/mysql

rpm -ivh ${mysql_server}
rpm -ivh ${mysql_client}
service mysql start
mysqladmin -uroot -proot
mysql -s -uroot -proot -e "grant all privileges on *.* to root @\"%\" identified by \"root\";"
mysql -s -uroot -proot -e "flush privileges;"

if [ "`rpm -qa|grep libevent`" != "" ]; then
	rpm -qa|grep libevent|xargs rpm -e --nodeps
fi
tar -xzvf ${libevent}
cd ${libevent_name}
./configure -prefix=/usr
make
make install
ln -s /usr/local/lib/libevent-2.0.so.5  /usr/lib/libevent-2.0.so.5
ln -s /usr/lib/libevent-2.0.so.5 /usr/lib64/libevent-2.0.so.5
cd ..

tar -xzvf ${memcached}
cd ${memcached_name}
./configure -prefix=/usr/local/memcached --with-libevent=/usr
make
make install
/usr/local/memcached/bin/memcached -d -p 11211 -u root -m 512m
cd ..

tar -zxvf ${tomcat}
cp -R ${tomcat_name} /usr/local/tomcat
/usr/local/tomcat/bin/startup.sh
/usr/local/tomcat/bin/shutdown.sh
service mysql restart

sed -i 's/<\/host>/<context><\/context>\n&/' server.xml
