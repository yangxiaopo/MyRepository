//发现查阅的资料对红黑树的讲解少个总结:
//
//红黑树是每个节点都带有颜色属性的二叉查找树，颜色为红色或黑色。在二叉查找树强制一般要求以外，对于任何有效的红黑树我们增加了如下的额外要求：
//  1.节点是红色或黑色。
//    2.根是黑色。
//    3.所有叶子都是黑色（NULL视为空）。
//    4.每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
//    5.从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。
//    根据规则4,新增节点必须为红色;
//    规定一下,要插入的节点标为N，N的父节点标为P，N的祖父节点标为G，N的叔父节点标为U
//    以下假设P为G的左子树,右子树对称操作而已

//红黑树是2-3-4树的一种等同.在2-3-4树上的插入和删除操作也等同于在红黑树中颜色翻转和旋转.尽管2-3-4树在实践中不经常使用。拿上笔
//
//                                               插入(insert)
//                                                     |
//   对于插入节点的父节点(P)为黑色时,不影响树的性质,END------插入节点的父节点(P)为红色时，由于插入之前就是一个红黑树,G就是黑色
//																									                                    |
//		                                                  那么U为黑色----------------------------------------------------------U为红色
//												                                    |																                                 |
//                               N为P的左子树P,G右旋,换色END <-------N为P的右子树,N,P左旋(转化为左子树)		  N为P的右子树,N,P左旋------>N为P的左子树 P,G右旋,N变黑(G此时为红)
//																																					|
//若G的父节点为黑.END-------若G的父节点为红，规则破坏,需将G视为插入节点N向上调整树,回到开始
//																															  
//																									
//												         


//1.最右边的那种情况P,N,U为红,G为黑的情况经过的旋转变色的结果和下述是一样的：
//	G为变为红色,2个字节点变为黑色.(此方法更快更节省内存SGI STL就是这么干的，还有其他的原因不赘述)
//2.换句话说,插入节点为左子树或右子树不影响,通过一次旋转就可以相互转化.只需要记2种情况，p,N同色/异色
//  而同色就用1,异色旋转END
//3.下篇 删除同样简单
//
//自此,插入结束；附上SGI STL源码


inline void 
_Rb_tree_rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
{
  __x->_M_color = _S_rb_tree_red;//新加入的节点必须为红(红黑树性质)
  while (__x != __root && __x->_M_parent->_M_color == _S_rb_tree_red) { //不是空树或者插入节点的父节点为红色时.
    if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left) {
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_right;
      if (__y && __y->_M_color == _S_rb_tree_red) { //(叔节点为红时)某节点X的2个子节点都为红时,将2个子节点的颜色改为黑,X改为红,循环知道根节点或符合红黑树规则.
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __y->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        __x = __x->_M_parent->_M_parent;
      }
      else {
        if (__x == __x->_M_parent->_M_right) { //叔父节点为黑色时,左右(右左)先做一次左旋(右旋),矫正为左左(右右).
          __x = __x->_M_parent;
          _Rb_tree_rotate_left(__x, __root);
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_right(__x->_M_parent->_M_parent, __root);
      }
    }
    else {//对称相反的操作
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_left;
      if (__y && __y->_M_color == _S_rb_tree_red) {
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __y->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        __x = __x->_M_parent->_M_parent;
      }
      else {
        if (__x == __x->_M_parent->_M_left) {
          __x = __x->_M_parent;
          _Rb_tree_rotate_right(__x, __root);
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_left(__x->_M_parent->_M_parent, __root);
      }
    }
  }
  __root->_M_color = _S_rb_tree_black;
}
