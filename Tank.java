import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.util.List;
import java.util.Random;

public class Tank {
	int x;//横坐标
	int y;//纵坐标
	public static final int WIDTH=30;//宽度
	public static final int HEIGHT=30;//高度
	public static final int XSPEED=5;//X轴速度
	public static final int YSPEED=5;//Y轴速度
	boolean orPlayerTank;//是否是玩家坦克
	private boolean alive=true;//是否存活
	Dir moveStatement=Dir.STOP;//移动状态
	Dir forward=Dir.D;//朝向，炮筒要用
	TankClient client;//有一个客户端的引用，用来与客户端交流
	
	//敌方坦克的移动和开火算法所需随机算子
	private Random r=new Random();
	private int countStep=r.nextInt(12)+3;
	
	//控制移动状态的工具
	boolean keyBoardU,keyBoardD,keyBoardL,keyBoardR;
	
	//tank构造方法
	public Tank(int x, int y, boolean orPlayerTank) {
		this.x = x;
		this.y = y;
		this.orPlayerTank = orPlayerTank;
	}
	public Tank(int x, int y, boolean orPlayerTank,Dir moveStatement,TankClient client) {
		this(x,y,orPlayerTank);
		this.moveStatement=moveStatement;
		this.client=client;
	}
	
	//画出坦克的draw()方法
	public void draw(Graphics g){
		//敌方坦克被摧毁后，客户端移除，自己坦克无敌
		if(!alive) {
			if(!orPlayerTank) {
				client.tanks.remove(this);			}
			return;
		}

		//画出敌我双方坦克
		Color c=g.getColor();
		if(orPlayerTank) g.setColor(Color.RED);
		else g.setColor(Color.BLUE);
		g.fillOval(x, y, WIDTH, HEIGHT);//画圆是用矩形画的，左上角的点位(x,y)
		g.setColor(c);
		
		//画炮筒
		switch (forward) {
		case U:
			g.drawLine(x+WIDTH/2, y+HEIGHT/2, x+WIDTH/2, y+HEIGHT);
			break;
		case L:	
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x, y + HEIGHT/2);
			break;
		case LU:
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x, y);
			break;
		case RU:
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x + WIDTH, y);
			break;
		case R:
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x + WIDTH, y + HEIGHT/2);
			break;
		case RD:
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x + WIDTH, y + HEIGHT);
			break;
		case D:
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x + WIDTH/2, y + HEIGHT);
			break;
		case LD:
			g.drawLine(x + WIDTH/2, y + HEIGHT/2, x, y + HEIGHT);
			break;
		}
		
		move();
	}
	
	private void move() {
		//移动
		switch (moveStatement) {
		case RU:
			x+=XSPEED;
			y-=YSPEED;
			break;
		case L:
			x -= XSPEED;
			break;
		case LU:
			x -= XSPEED;
			y -= YSPEED;
			break;
		case U:
			y -= YSPEED;
			break;
		case R:
			x += XSPEED;
			break;
		case RD:
			x += XSPEED;
			y += YSPEED;
			break;
		case D:
			y += YSPEED;
			break;
		case LD:
			x -= XSPEED;
			y += YSPEED;
			break;
		case STOP:
			break;
		}
		
		//只要在移动，就让移动状态等于前进方向
		if(moveStatement!=Dir.STOP) {
			forward=moveStatement;
		}
		
		//考虑边界问题
		if(x<0)x=0;//左边界
		if(x+WIDTH>TankClient.GAME_HEIGHT)x=TankClient.GAME_HEIGHT-WIDTH;//右边界
		if(y<0)y=0;//上边界
		if(y+HEIGHT>TankClient.GAME_HEIGHT)y=TankClient.GAME_HEIGHT-HEIGHT;//下边界
		
		//随机步数随机方向
		//敌方坦克的移动和开火算法
		if(!orPlayerTank) {
			if(countStep==0) {
				countStep=r.nextInt(12)+3;
				Dir[] dirs=Dir.values();
				moveStatement=dirs[r.nextInt(dirs.length)];
			}
			countStep--;
			if(r.nextInt(41)>38) this.fire();
		}
	}
	
	//开火
	private Bullet fire() {
		int x=this.x + WIDTH/2 - Bullet.WIDTH/2;
		int y=this.y + HEIGHT/2 - Bullet.HEIGHT/2;
		Bullet b=new Bullet(x,y,this.orPlayerTank,forward,client);
		client.bullets.add(b);
		return b;
	}
	
	//判断碰撞体积
	public Rectangle getRect() {
		return new Rectangle(x, y, WIDTH, HEIGHT);
	}

	public boolean isAlive() {
		return alive;
	}

	public void setAlive(boolean alive) {
		this.alive = alive;
	}
	
	//有KeyAdapter调用--------实现有键盘按键控制坦克移动状态
	//按下键
	public void keyPressed(KeyEvent e) {
		int key=e.getKeyCode();
		switch (key) {
		case KeyEvent.VK_CONTROL:
			fire();
			break;
		case KeyEvent.VK_UP:
			keyBoardU=true;
			break;
		case KeyEvent.VK_DOWN:
			keyBoardD=true;
			break;
		case KeyEvent.VK_LEFT:
			keyBoardL=true;
			break;
		case KeyEvent.VK_RIGHT:
			keyBoardR=true;
			break;
		}
		controlDirection();
	}
	
	//按键控制移动状态
	public void controlDirection() {
		if(keyBoardU&&!keyBoardD&&!keyBoardL&&!keyBoardR) moveStatement=Dir.U;
		else if(keyBoardU&&keyBoardL&&!keyBoardD&&!keyBoardR) moveStatement=Dir.LU;
		else if(!keyBoardU&&!keyBoardL&&!keyBoardD&&keyBoardR) moveStatement=Dir.R;
		else if(!keyBoardU&&!keyBoardL&&keyBoardD&&keyBoardR) moveStatement=Dir.RD;
		else if(!keyBoardU&&!keyBoardL&&keyBoardD&&!keyBoardR) moveStatement=Dir.D;
		else if(!keyBoardU&&keyBoardL&&keyBoardD&&!keyBoardR) moveStatement=Dir.LD;
		else if(!keyBoardU&&keyBoardL&&!keyBoardD&&!keyBoardR) moveStatement=Dir.L;
		else if(keyBoardU&&!keyBoardL&&!keyBoardD&&keyBoardR) moveStatement=Dir.RU;
		else if(!keyBoardU&&!keyBoardL&&!keyBoardD&&!keyBoardR) moveStatement=Dir.STOP;
	}
	
	public void keyReleased(KeyEvent e) {
		int key=e.getKeyCode();
		switch (key) {
		case KeyEvent.VK_UP:
			keyBoardU=false;
			break;
		case KeyEvent.VK_DOWN:
			keyBoardD=false;
			break;
		case KeyEvent.VK_LEFT:
			keyBoardL=false;
			break;
		case KeyEvent.VK_RIGHT:
			keyBoardR=false;
			break;
		}
		controlDirection();
	}
	
	//判断坦克与坦克的撞击
		public boolean impact(Tank t) {
			//判断如果2者都是有效的，且坦克和坦克 属于不同阵营，产生交叉时 爆炸
			if(this.isAlive()&&t.isAlive()&&this.orPlayerTank!=t.orPlayerTank&&this.getRect().intersects(t.getRect())) {
				this.setAlive(false);
				t.setAlive(false);
				client.explodes.add(new Explode(x,y,client));
				return true;
			}
			return false;
		}
		
		public boolean impact(List<Tank> tanks) {
			for(int i=0;i<tanks.size();i++) {
				if(this.impact(tanks.get(i))) {
					return true;
				}
			}
			return false;
		}
}
