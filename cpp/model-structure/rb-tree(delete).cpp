//删除某个节点其实是删除某个节点的值
//又节点删除之后需要找到此节点的后继;
//那么不如找到删除节点的后继节点，更换2个节点的值，而将后继节点当作真正被删除的节点.
//
//而所谓后继节点,他最多只有一个子节点.这就将问题简化.
//
//		设要删除的节点A的后继节点Y,Y的父节点为P,兄弟节点为S,兄弟节点左子节点为SL,兄弟节点右子节点为SR
//				|
//Y为红色直接删除,END -------------------------Y为黑色时,需要调整,后继节点Y最多一个非空子节点,记为X,此时,X是直接替换Y的
//								|
//			X为红色时,直接变黑,达到平衡.END---------------------------X为黑色时
//										  |
//					            兄弟节点S为黑色   <----------------------- 兄弟节点(S)为红色时,据红黑树性质,5个颜色固定.P S左旋,换色.转换为S为黑的情形
//						    	|	 	
//				SL SR同黑--------------------------------------------------------
//				   |								|
//(全黑)P为黑色,S变红 整个子树平衡,----------P为红色,P S换色END	SR为红,P S左旋 换色,SR变黑.END<-------SL为红, SR为黑,SL S变色 右旋转化为SR为红的情况
//但是整个子树相对于其他子树少一个黑,
//于是将P视为X循环调整.


//红黑树至此结束
//最后附上SGI　STL红黑树删除操作的代码

inline _Rb_tree_node_base*
_Rb_tree_rebalance_for_erase(_Rb_tree_node_base* __z,
                             _Rb_tree_node_base*& __root,
                             _Rb_tree_node_base*& __leftmost,
                             _Rb_tree_node_base*& __rightmost)
{
  _Rb_tree_node_base* __y = __z;
  _Rb_tree_node_base* __x = 0;
  _Rb_tree_node_base* __x_parent = 0;
  if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
    __x = __y->_M_right;     // __x might be null.
  else
    if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
      __x = __y->_M_left;    // __x is not null.
    else {                   // __z has two non-null children.  Set __y to
      __y = __y->_M_right;   //   __z's successor.  __x might be null.
      while (__y->_M_left != 0)
        __y = __y->_M_left;
      __x = __y->_M_right;
    }
  if (__y != __z) {          // relink y in place of z.  y is z's successor 删除很简单,主要是删除后的调整.
    __z->_M_left->_M_parent = __y; 
    __y->_M_left = __z->_M_left;
    if (__y != __z->_M_right) {
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;
      __y->_M_parent->_M_left = __x;      // __y must be a child of _M_left
      __y->_M_right = __z->_M_right;
      __z->_M_right->_M_parent = __y;
    }
    else
      __x_parent = __y;  
    if (__root == __z)
      __root = __y;
    else if (__z->_M_parent->_M_left == __z)
      __z->_M_parent->_M_left = __y;
    else 
      __z->_M_parent->_M_right = __y;
    __y->_M_parent = __z->_M_parent;
    __STD::swap(__y->_M_color, __z->_M_color);
    __y = __z;
    // __y now points to node to be actually deleted
  }
  else {                        // __y == __z
    __x_parent = __y->_M_parent;
    if (__x) __x->_M_parent = __y->_M_parent;   
    if (__root == __z)
      __root = __x;
    else 
      if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __x;
      else
        __z->_M_parent->_M_right = __x;
    if (__leftmost == __z) 
      if (__z->_M_right == 0)        // __z->_M_left must be null also
        __leftmost = __z->_M_parent;
    // makes __leftmost == _M_header if __z == __root
      else
        __leftmost = _Rb_tree_node_base::_S_minimum(__x);
    if (__rightmost == __z)  
      if (__z->_M_left == 0)         // __z->_M_right must be null also
        __rightmost = __z->_M_parent;  
    // makes __rightmost == _M_header if __z == __root
      else                      // __x == __z->_M_left
        __rightmost = _Rb_tree_node_base::_S_maximum(__x);
  }
  if (__y->_M_color != _S_rb_tree_red) {  //y不为红色,进行调整.
    while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
      if (__x == __x_parent->_M_left) {                                          //删除后调整.
        _Rb_tree_node_base* __w = __x_parent->_M_right;
        if (__w->_M_color == _S_rb_tree_red) {/////////////////////////////////////x(黑)w(红)-->x(黑)w(黑)
          __w->_M_color = _S_rb_tree_black;                                      //
          __x_parent->_M_color = _S_rb_tree_red;                                 //
          _Rb_tree_rotate_left(__x_parent, __root);                              //
          __w = __x_parent->_M_right;                                            //
        }                                                                        //
        if ((__w->_M_left == 0 ||                                                //
             __w->_M_left->_M_color == _S_rb_tree_black) &&                      //
            (__w->_M_right == 0 ||                                               //
             __w->_M_right->_M_color == _S_rb_tree_black)) {///////////////////////w(黑)的2个子节点为黑时(NULL默认为黑)  [此时若__x = __x_parent为红,跳出循环]
          __w->_M_color = _S_rb_tree_red;                                        //
          __x = __x_parent;                                                      //
          __x_parent = __x_parent->_M_parent;                                    //
        } else {                                                                 //
          if (__w->_M_right == 0 ||                                              //
              __w->_M_right->_M_color == _S_rb_tree_black) {                     //
            if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;///////////w->left(红)w->right(黑)-->w->left(黑)w->right(红)
            __w->_M_color = _S_rb_tree_red;                                      //
            _Rb_tree_rotate_right(__w, __root);                                  //
            __w = __x_parent->_M_right;                                          //
          }                                                                      //
          __w->_M_color = __x_parent->_M_color;////////////////////////////////////x(黑)w(黑)w->right(红)成功平衡
          __x_parent->_M_color = _S_rb_tree_black;                               //
          if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;         //
          _Rb_tree_rotate_left(__x_parent, __root);                              //
          break;                                                                 //
        }////////////////////////////////////////////////////////////////////////// 
      } else {                  // same as above, with _M_right <-> _M_left.
        _Rb_tree_node_base* __w = __x_parent->_M_left;
        if (__w->_M_color == _S_rb_tree_red) {
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rb_tree_rotate_right(__x_parent, __root);
          __w = __x_parent->_M_left;
        }
        if ((__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black) &&
            (__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black)) {
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_left == 0 || 
              __w->_M_left->_M_color == _S_rb_tree_black) {
            if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rb_tree_rotate_left(__w, __root);
            __w = __x_parent->_M_left;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
          _Rb_tree_rotate_right(__x_parent, __root);
          break;
        }
      }
    if (__x) __x->_M_color = _S_rb_tree_black;/////////////////////////////////////最后处理x_parent(红)其他全为黑 将x_parent变为黑就成功平衡.(while循环之外)
  }
  return __y;
}
