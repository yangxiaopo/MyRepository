//ɾ��ĳ���ڵ���ʵ��ɾ��ĳ���ڵ��ֵ
//�ֽڵ�ɾ��֮����Ҫ�ҵ��˽ڵ�ĺ��;
//��ô�����ҵ�ɾ���ڵ�ĺ�̽ڵ㣬����2���ڵ��ֵ��������̽ڵ㵱��������ɾ���Ľڵ�.
//
//����ν��̽ڵ�,�����ֻ��һ���ӽڵ�.��ͽ������.
//
//		��Ҫɾ���Ľڵ�A�ĺ�̽ڵ�Y,Y�ĸ��ڵ�ΪP,�ֵܽڵ�ΪS,�ֵܽڵ����ӽڵ�ΪSL,�ֵܽڵ����ӽڵ�ΪSR
//				|
//YΪ��ɫֱ��ɾ��,END -------------------------YΪ��ɫʱ,��Ҫ����,��̽ڵ�Y���һ���ǿ��ӽڵ�,��ΪX,��ʱ,X��ֱ���滻Y��
//								|
//			XΪ��ɫʱ,ֱ�ӱ��,�ﵽƽ��.END---------------------------XΪ��ɫʱ
//										  |
//					            �ֵܽڵ�SΪ��ɫ   <----------------------- �ֵܽڵ�(S)Ϊ��ɫʱ,�ݺ��������,5����ɫ�̶�.P S����,��ɫ.ת��ΪSΪ�ڵ�����
//						    	|	 	
//				SL SRͬ��--------------------------------------------------------
//				   |								|
//(ȫ��)PΪ��ɫ,S��� ��������ƽ��,----------PΪ��ɫ,P S��ɫEND	SRΪ��,P S���� ��ɫ,SR���.END<-------SLΪ��, SRΪ��,SL S��ɫ ����ת��ΪSRΪ������
//���������������������������һ����,
//���ǽ�P��ΪXѭ������.


//��������˽���
//�����SGI��STL�����ɾ�������Ĵ���

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
  if (__y != __z) {          // relink y in place of z.  y is z's successor ɾ���ܼ�,��Ҫ��ɾ����ĵ���.
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
  if (__y->_M_color != _S_rb_tree_red) {  //y��Ϊ��ɫ,���е���.
    while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
      if (__x == __x_parent->_M_left) {                                          //ɾ�������.
        _Rb_tree_node_base* __w = __x_parent->_M_right;
        if (__w->_M_color == _S_rb_tree_red) {/////////////////////////////////////x(��)w(��)-->x(��)w(��)
          __w->_M_color = _S_rb_tree_black;                                      //
          __x_parent->_M_color = _S_rb_tree_red;                                 //
          _Rb_tree_rotate_left(__x_parent, __root);                              //
          __w = __x_parent->_M_right;                                            //
        }                                                                        //
        if ((__w->_M_left == 0 ||                                                //
             __w->_M_left->_M_color == _S_rb_tree_black) &&                      //
            (__w->_M_right == 0 ||                                               //
             __w->_M_right->_M_color == _S_rb_tree_black)) {///////////////////////w(��)��2���ӽڵ�Ϊ��ʱ(NULLĬ��Ϊ��)  [��ʱ��__x = __x_parentΪ��,����ѭ��]
          __w->_M_color = _S_rb_tree_red;                                        //
          __x = __x_parent;                                                      //
          __x_parent = __x_parent->_M_parent;                                    //
        } else {                                                                 //
          if (__w->_M_right == 0 ||                                              //
              __w->_M_right->_M_color == _S_rb_tree_black) {                     //
            if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;///////////w->left(��)w->right(��)-->w->left(��)w->right(��)
            __w->_M_color = _S_rb_tree_red;                                      //
            _Rb_tree_rotate_right(__w, __root);                                  //
            __w = __x_parent->_M_right;                                          //
          }                                                                      //
          __w->_M_color = __x_parent->_M_color;////////////////////////////////////x(��)w(��)w->right(��)�ɹ�ƽ��
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
    if (__x) __x->_M_color = _S_rb_tree_black;/////////////////////////////////////�����x_parent(��)����ȫΪ�� ��x_parent��Ϊ�ھͳɹ�ƽ��.(whileѭ��֮��)
  }
  return __y;
}
