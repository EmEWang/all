#include "tree.h"




void gotoxy(int x, int y)
{
	// 更新光标位置
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
}

// 获取树的深度
int BiTreeDepth(BiTree T) {
	if (T == NULL) return 0;

	int depthLeft, depthRight;
	depthLeft = BiTreeDepth(T->lchild);
	depthRight = BiTreeDepth(T->rchild);

	return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
}

// 将二叉树分为根，左子树，右子树三个部分
Status BreakBiTree(BiTree& T, BiTree& L, BiTree& R) {
	if (T == NULL) return ERROR;
	L = T->lchild;
	R = T->rchild;

	return OK;
}

Status Traverse_R(BiTree T, int depth, int right, int tap) {
	if (T == NULL) return OK;

	// 获取一次树的初始高度，用于计算相对偏移数量
	static int treeDepth = BiTreeDepth(T);
	// 记录当前光标位置，用于在递归中记录当前递归时树的位置
	int x, y;
	// 拆分树，将树的左右子树拆分开来
	BiTree L, R;
	BreakBiTree(T, L, R);

	// 计算父树的偏移量
	int tap1 = tap * pow(2, treeDepth - depth);
	// 计算子树的偏移量
	int tap2 = right * (pow(2, treeDepth - depth));
	// 计算半偏移量
	int tap3 = pow(2, treeDepth - depth - 1);

	// 获取根的坐标
	// x 计算方法为：父偏移量 + 子偏移量 + 半偏移量 - 1
	// y 计算方法为：目前打印的层数 * 2
	x = tap1 + tap2 + tap3 - 1;
	y = depth * 2;

	// 打印根的位置
	gotoxy(x * 2, y);
	printf("%d", T->data);

	// 在打印子树时，当前层数+1
	depth++;
	// 计算子树的父偏移量
	tap = tap * 2 + (right == 1 ? 2 : 0);
	if (L == NULL && R == NULL) return OK;
	else if (R == NULL) {
		// 打印左子树的位置
		gotoxy(x * 2 - tap3, y + 1);
		printf("┏");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┛");
		Traverse_R(L, depth, 0, tap);
	}
	else if (L == NULL) {
		// 打印右子树的位置
		gotoxy(x * 2, y + 1);
		printf("┗");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┓");
		Traverse_R(R, depth, 1, tap);
	}
	else {
		// 打印左右子树的位置
		gotoxy(x * 2 - tap3, y + 1);
		printf("┏");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┻");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┓");
		Traverse_R(L, depth, 0, tap);
		Traverse_R(R, depth, 1, tap);
	}
}

Status Traverse(BiTree T) {
	Traverse_R(T, 0, 0, 0);
	return OK;
}



namespace wjg
{

	template <class type>
	node_t<type>::node_t()
	{
	}


	template <class type>
	node_t_b<type>::node_t_b()
	{
		m_left = NULL;
		m_right = NULL;		
	}
	
	template <class type>
	node_t_b_avl<type>::node_t_b_avl()
	{
		m_balance = 0;
	}

	
	//tree
	template <class type>
	tree<type>::tree(){
		m_root = NULL;
		m_cur  = NULL;
		m_size = 0;
	}

	template <class type>
	bool tree<type>::insert(type key){
		return true;
	}

	template <class type>
	bool tree<type>::erase(type key){
		return true;
	}

	template <class type>
	bool tree<type>::clear(){
		return true;
	}

	template <class type>
	int tree<type>::size(){
		return m_size;
	}

	template <class type>
	int tree<type>::depth() {
		return m_depth;
	}

	template <class type>
	node_t<type>* tree<type>::next(){
		return NULL;
	}


	// tree_b

	template <class type>
	tree_b<type>::tree_b() {
	}

	template <class type>
	bool tree_b<type>::insert(type key) {
		return true;
	}

	template <class type>
	bool tree_b<type>::erase(type key) {
		return true;
	}

	template <class type>
	bool tree_b<type>::clear() {
		return true;
	}

	template <class type>
	int tree_b<type>::size() {

		return tree<type>::size();
	}

	template <class type>
	int tree_b<type>::depth() {
		return tree<type>::depth();
	}

	template <class type>
	node_t<type>* tree_b<type>::next() {
		return NULL;
	}



	// tree_b_avl

	template <class type>
	tree_b_avl<type>::tree_b_avl() {
	}

	template <class type>
	bool tree_b_avl<type>::insert(type key) {
		return true;
	}

	template <class type>
	bool tree_b_avl<type>::erase(type key) {
		return true;
	}

	template <class type>
	bool tree_b_avl<type>::clear() {
		return true;
	}

	template <class type>
	int tree_b_avl<type>::size() {

		return tree<type>::size();
	}

	template <class type>
	int tree_b_avl<type>::depth() {
		return tree<type>::depth();
	}

	template <class type>
	node_t<type>* tree_b_avl<type>::next() {
		return NULL;
	}



	//tree_simple_avl
	tree_simple_avl::tree_simple_avl()
	{
		m_root = NULL;
	}
	node_simple* tree_simple_avl::insert(node_simple* node, node_simple* root, bool rebuild)
	{
		if (!node)
		{
			return root;
		}

		if (!m_root)
		{
			m_root = node;
			return node;
		}

		node_simple* cur = m_root;

		if (rebuild)
		{
			goto rebuild;
		}

		//while (1)
		//{
		//	if (node->key == cur->key)
		//	{
		//		return false;
		//	}

		//	if (node->key < cur->key)
		//	{
		//		if (!(cur->left))
		//		{
		//			cur->left = node;
		//			return true;
		//		}
		//		else
		//		{
		//			cur = cur->left;
		//			continue;
		//		}
		//	}

		//	if (node->key > cur->key)
		//	{
		//		if (!(cur->right))
		//		{
		//			cur->right = node;
		//			return true;
		//		}
		//		else
		//		{
		//			cur = cur->right;
		//			continue;
		//		}
		//	}
		//}

	rebuild:
		cur = root;
		if (node->key == cur->key)
		{
			return cur;
		}

		if (node->key < cur->key)
		{
			return insert(node, cur->left, rebuild);
		}

		if (node->key > cur->key)
		{
			return insert(node, cur->right, rebuild);
		}

		node_simple* tmpnode = nullptr;
		cur-> weight = max(height(cur->left), height(cur->right)) + 1;
		int balan = balance(cur);

		if (balan > 1 && node->key < cur->left->key)
		{
			tmpnode = ll_rotate(cur);
		}

		if (balan > 1 && node->key > cur->left->key)
		{
			tmpnode = lr_rotate(cur);
		}

		if (balan < -1 && node->key > cur->right->key)
		{
			tmpnode = rr_rotate(cur);
		}

		if (balan < -1 && node->key < cur->right->key)
		{
			tmpnode = rl_rotate(cur);
		}

		return tmpnode;
	}

	node_simple* tree_simple_avl::insert(node_simple* root, int key)
	{
		if (!root)
		{
			node_simple* node = new node_simple(key);
			return node;
		}
		
		if (root->key == key)
		{
			return root;
		}
		else if(key < root->key)
		{
			root->left = insert(root->left, key);
		}
		else
		{
			root->right = insert(root->right, key);
		}

		root->weight = max(height(root->left), height(root->right)) + 1;

		int balan = balance(root);
		node_simple* tmpnode = root;

		if (balan > 1 && key < root->left->key)
		{
			tmpnode = ll_rotate(root);
		}
		else if (balan > 1 && key > root->left->key)
		{
			tmpnode = lr_rotate(root);
		}
		else if (balan < -1 && key < root->right->key)
		{
			tmpnode = rl_rotate(root);
		}
		else if (balan < -1 && key > root->right->key)
		{
			tmpnode = rr_rotate(root);
		}


		return tmpnode;
	}

	node_simple* tree_simple_avl::remove(node_simple* root, int key)
	{
		return nullptr;
	}

	bool tree_simple_avl::insert(int node, bool rebuild)
	{
		node_simple* pnode = new node_simple(node);
		bool b = insert(pnode, m_root,rebuild);
		if (!b)
		{
			delete pnode;
		}
		return b;
	}

	bool tree_simple_avl::insert(int node)
	{
		m_root = insert(m_root, node);
		return false;
	}

	node_simple* tree_simple_avl::erase(node_simple* root, int key)
	{
		if (!root)
		{
			return root;
		}

		if (key < root->key)
		{
			root->left = erase(root->left, key);
		}
		else if (key > root->key)
		{
			root->right = erase(root->right, key);
		}
		else
		{
			if (!root->left || !root->right)
			{
				node_simple* node = root->left ? root->left : root->right;

				delete root;
				root = node;

				//node_simple* temp = root->left ? root->left : root->right;

				//if (temp == NULL)
				//{
				//	temp = root;
				//	root = NULL;
				//}
				//else
				//	*root = *temp;
				//free(temp);

			}
			else
			{
				node_simple* node = minValueNode(root->right);
				root->key = node->key;
				root->right = erase(root->right, root->key);

				

			}
		}

		if (!root)
		{
			return root;
		}

		root->weight = height(root);
		int balan = balance(root);

		if (balan > 1 && balance(root->left) >= 0)
		{
			return ll_rotate(root);
		}

		if (balan > 1 && balance(root->left) < 0)
		{
			return lr_rotate(root);
		}

		if (balan < -1 && balance(root->left) >= 0)
		{
			return rl_rotate(root);
		}

		if (balan < -1 && balance(root->left) < 0)
		{
			return rr_rotate(root);
		}

		return root;
	}

	node_simple* tree_simple_avl::erase(int key)
	{
		m_root = erase(m_root, key);
		return m_root;
	}

	//由于在A的左孩子(L)的左子树(L)上插入新结点，使原来平衡二叉树变得不平衡，此时A的平衡因子由1增至2。
	//下图1是LL型的最简单形式。显然，按照大小关系，结点B应作为新的根结点，其余两个节点分别作为左右孩子节点才能平衡，
	//A结点就好像是绕结点B顺时针旋转一样。
	//           A                     B                          
	//          /       LL            / \                          
	//         B      ----->         C   A                              
	//        /                                                 
	//       C                                                  
	//                                                         
	//LL型调整的一般形式如下图2所示，表示在A的左孩子B的左子树BL(不一定为空)中插入结点(图中阴影部分所示)而导致不平衡( h 表示子树的深度)。
	//这种情况调整如下：①将A的左孩子B提升为新的根结点；
	// ②将原来的根结点A降为B的右孩子；
	// ③各子树按大小关系连接(BL和AR不变，BR调整为A的左子树)。
	// 
	//             A                                                   
	//          /     \               LL                                  
	//        B        █↑           ----->             B                           
	//      /  \      ARh                           /     \                   
	//     █↑   █↑     █↓                          █↑       A                    
	//    BLh  BRh                                BLh     /   \                   
	//     █↓   █↓                                 █↓    █↑    █↑        
	//     ▲1                                      ▲1   BRh   ARh                    
	//     ▧                                       ▧     █↓    █↓                   
	//                                                                               
	//                                                                                 
	//                                                                    
	//                                                        
	node_simple* tree_simple_avl::ll_rotate(node_simple* xnode)
	{
		if (!xnode || !xnode->left || !xnode->left->left)
		{
			return xnode;
		}

		node_simple* ynode = xnode->left;
		xnode->left = ynode->right;
		ynode->right = xnode;

		//xnode->weight = max(xnode->left->weight, xnode->right->weight) + 1;
		//ynode->weight = max(ynode->left->weight, ynode->right->weight) + 1;
		xnode->weight = height(xnode);
		ynode->weight = height(ynode);
		return ynode;
	}


	//由于在A的右孩子(R)的右子树(R)上插入新结点，使原来平衡二叉树变得不平衡，此时A的平衡因子由-1变为-2。
	//图3是RR型的最简单形式。显然，按照大小关系，结点B应作为新的根结点，其余两个节点分别作为左右孩子节点才能平衡，
	//A结点就好像是绕结点B逆时针旋转一样。
	//     A                         B                          
	//      \         RR            / \                          
	//       B      ----->         A   C                              
	//        \                                                 
	//         C                                                 
	//                                                         
	//RR型调整的一般形式如下图4所示，表示在A的右孩子B的右子树BR(不一定为空)中插入结点(图中阴影部分所示)而导致不平衡( h 表示子树的深度)。
	//这种情况调整如下：
	//将A的右孩子B提升为新的根结点；
	//将原来的根结点A降为B的左孩子
	//各子树按大小关系连接(AL和BR不变，BL调整为A的右子树)。
	// 
	//             A                                                   
	//          /     \               RR                                  
	//         █↑      B            ----->                   B                           
	//        ALh    /   \                                /     \                   
	//         █↓   █↑    █↑                             A       █↑
	//             BLh   BRh                            / \     BRh     
	//              █↓    █↓                           █↑  █↑    █↓
	//                    ▲1                          ALh BLh    ▲1          
	//                    ▧                            █↓  █↓    ▧          
	//                                                                 
	//                                                                                 
	//                                                                    
	//                                                        
	node_simple* tree_simple_avl::rr_rotate(node_simple* xnode)
	{
		if (!xnode || !xnode->right || !xnode->right->right)
		{
			return xnode;
		}

		node_simple* ynode = xnode->right;
		xnode->right = ynode->left;
		ynode->left = xnode;

		//xnode->weight = max(xnode->left->weight, xnode->right->weight) + 1;
		//ynode->weight = max(ynode->left->weight, ynode->right->weight) + 1;
		xnode->weight = height(xnode);
		ynode->weight = height(ynode);
		return ynode;

		return nullptr;
	}

	//由于在A的左孩子(L)的右子树(R)上插入新结点，使原来平衡二叉树变得不平衡，此时A的平衡因子由1变为2。
	// 图5是LR型的最简单形式。显然，按照大小关系，结点C应作为新的根结点，其余两个节点分别作为左右孩子节点才能平衡。
	//           A                     C                          
	//          /       LR            / \                          
	//         B      ----->         B   A                              
	//          \                                                
	//           C                                               
	//                                                         
	//LR型调整的一般形式如下图6所示，表示在A的左孩子B的右子树(根结点为C，不一定为空)中插入结点(图中两个阴影部分之一)而导致不平衡( h 表示子树的深度)。
	// 这种情况调整如下：
	// ①将B的左孩子C提升为新的根结点；
	// ②将原来的根结点A降为C的右孩子；
	// ③各子树按大小关系连接(BL和AR不变，CL和CR分别调整为B的右子树和A的左子树)。
	// 
	//             A                                                   
	//          /     \                LR                                  
	//        B         █↑           ----->              C                            
	//      /   \      AR                            /      \                   
	//     █↑     C     █h                         B          A                    
	//    BL    /   \   █                        /   \       /   \                   
	//     █h  █↑    █↑ █↓                      █↑    █↑    █↑    █↑    
	//     █  CLh-1 CRh-1                      BL    CLh-1 CRh-1 AR                   
	//     █↓  █↓    █↓                         █h    █↓    █↓    █h              
	//         ▲1    ▲1                         █     ▲1    ▲1    █                
	//         ▧     ▧                          █↓    ▧     ▧     █↓                  
	//                                                                   
	//  代码中                                              
	//                                                                   
	//                                     ↘                  
	//                5x                     5x                                               
	//           ↘  /  \       RR          /  \          LL                          
	//             2y    6    ----->       3    6       ----->       3                                  
	//            / \                     / \                     /     \                    
	//           1   3                   2y  ▲4                  2y     5x                                  
	//              /  \                / \                     / \    /  \                      
	//             △4  ▲4              1  △4                   1  △4  ▲4  6                              
	//                                                        
	node_simple* tree_simple_avl::lr_rotate(node_simple* xnode)
	{
		node_simple* ynode = xnode->left;
		xnode->left = rr_rotate(ynode);
		return ll_rotate(xnode);
		return nullptr;
	}


	//由于在A的右孩子(R)的左子树(L)上插入新结点，使原来平衡二叉树变得不平衡，此时A的平衡因子由-1变为-2。
	// 图7是RL型的最简单形式。显然，按照大小关系，结点C应作为新的根结点，其余两个节点分别作为左右孩子节点才能平衡。
	//         A                       C                          
	//          \       RL            / \                          
	//           B    ----->         A   B                              
	//          /                                                
	//         C                                                 
	//                                                         
	//RL型调整的一般形式如下图8所示，表示在A的右孩子B的左子树(根结点为C，不一定为空)中插入结点(图中两个阴影部分之一)而导致不平衡( h 表示子树的深度)。
	//这种情况调整如下：
	// ①将B的左孩子C提升为新的根结点；
	// ②将原来的根结点A降为C的左孩子；
	// ③各子树按大小关系连接(AL和BR不变，CL和CR分别调整为A的右子树和B的左子树)。
	// 
	//             A                                                   
	//         /       \                     RL                                  
	//                    B                ----->             C                            
	//       █↑        /     \                            /      \                   
	//      AL        C         █↑                       A         B                    
	//       █h      /   \     BR                     /   \       /   \                   
	//       █      █↑    █↑    █h                   █↑    █↑    █↑    █↑    
	//       █↓    CLh-1 CRh-1  █                   AL    CLh-1 CRh-1 BR                   
	//              █↓    █↓    █↓                   █h    █↓    █↓    █h              
	//              ▲1    ▲1                         █     ▲1    ▲1    █                
	//              ▧     ▧                          █↓    ▧     ▧     █↓                  
	//                                                                  
	//  代码中                                              
	//                                                                   
	//                                      ↘                  
	//                2x                      2x                                               
	//               /  \  ↙      LL         /  \         RR                          
	//              1    5y      ----->      1    4        -----        4                                  
	//                  / \                      / \                  /   \                    
	//                 4   6                    △3  5y               2x    5y                                  
	//                / \                          /  \              / \   / \                      
	//               △3 ▲3                       ▲3    6            1 △3  ▲3 6                              
	//       							   
	node_simple* tree_simple_avl::rl_rotate(node_simple* xnode)
	{
		node_simple* ynode = xnode->right;
		xnode->right = ll_rotate(ynode);
		return rr_rotate(xnode);
		return nullptr;
	}

	int tree_simple_avl::height(node_simple* node)
	{
		if (!node)
		{
			return 0;
		}
		return max(height(node->left), height(node->right)) + 1;
	}

	int tree_simple_avl::balance(node_simple* node)
	{
		if (!node)
		{
			return 0;
		}

		return height(node->left) - height(node->right);
	}

	void tree_simple_avl::print(node_simple* node, int len, int skip, float x, int y, float step)
	{

		// ⬎ ⬏ ⬐ ⬑ ↵ ↓ ↔ ← → ↑ - —
		// ━ ┏ ┓
		// `ˊᐟ‐‑‒―⁃≣⋐⋑⋒⋓⌒⌜⌝⌞⌟⎯─━│┃┄┅┆┇┈┉┊┋┌┍┎┏┐┑┒┓└└┕┖┗┘┙┚┛├├┝┞┟┠┡┢┣┤┥┦┧┨┩┪┫┬┭┮┳┴┵┶┷┸┹┺┻┼┽┾┿╀╁╂╃╄╅╆╇╈╉╊╋╌╍╎╏══║╒╓╔╔╔╕╕╖╖╗╗╘╙╚╚╛╛╜╜╝╝╞╟╟╠╡╡╢╢╣╣╤╤╥╥╦╦╧╧╨╨╩╩╪╪╫╬╬╭╮╯╰╱╲╳╴╵╶╷╸╹╺╻╼╽╾╿▏▕◜◝◞◟◠◡☰☱☲☳☴☵☶☷✕≡⌈⌊—⌉⌋

		if (!node)
		{
			return;
		}

		gotoxy(x, y);
		printf("%d", node->key);

		float xl = x - step / 2;
		float xr = x + step / 2;

		if (node->left)
		{
			for (int i = xl; i < (int)x; i++)
			{
				gotoxy(i, y + 1);
				if (i == (int)xl)
				{
					printf("┏");
				}
				else
				{
					printf("━");
				}
			}			
			print(node->left, len, skip, xl, y+2, step/2);
		}
		
		if (node->right)
		{
			for (int i = x ; i <= (int)xr; i++)
			{
				gotoxy(i, y + 1);
				if (i == (int)(xr))
				{
					printf("┓");
				}
				else
				{
					printf("━");
				}
			}
			print(node->right, len, skip, xr, y + 2, step/2);
		}
	}

	int tree_simple_avl::print(int y)
	{
		if (!m_root)
		{
			return 1;
		}

		int h = m_root->weight;
		int len = 2;
		int skip = 1;
		int lenmax = pow(2, h - 1) * (len + skip) - skip;

		float x = lenmax / 2.0 - len / 2.0;
		//int y = 0;

		print(m_root, len, skip, x, y, x);

		gotoxy(0, h * 2 + y);

		for (int i= 0;i< lenmax;i++)
		{
			printf("-");
		}

		printf("\n");

		return h * 2 + 1;
	}

	node_simple* tree_simple_avl::minValueNode(node_simple* root)
	{
		if (!root)
		{
			return root;
		}

		node_simple* cur = root;
		while (cur->left!=nullptr)
		{
			cur = cur->left;
		}

		return cur;
	}

	void tree_simple_avl::preoder(node_simple* node)
	{
		if (!node)
		{
			return;
		}

		printf("%d ", node->key);
		preoder(node->left);
		preoder(node->right);
	}

	void tree_simple_avl::preoder()
	{
		printf("preoder\n");
		preoder(m_root);
		printf("\n");
	}

	void tree_simple_avl::midoder(node_simple* node)
	{
		if (!node)
		{
			return;
		}
		
		midoder(node->left);
		printf("%d ", node->key);
		midoder(node->right);
	}

	void tree_simple_avl::midoder()
	{
		printf("midoder\n");
		midoder(m_root);
		printf("\n");
	}

	void tree_simple_avl::postoder(node_simple* node)
	{
		if (!node)
		{
			return;
		}

		postoder(node->left);
		postoder(node->right);
		printf("%d ", node->key);
	}

	void tree_simple_avl::postoder()
	{
		printf("postoder\n");
		postoder(m_root);
		printf("\n");
	}


	// BFS实现二叉树的深度计算
	int tree_simple_avl::bfs(node_simple* root)
	{
		if (root == NULL) return 0;
		int dep = 0;
		std::queue<node_simple*> q_node;
		q_node.push(root);
		while (!q_node.empty())
		{
			int n_size = q_node.size();
			for (int i = 0; i < n_size; i++)
			{
				node_simple* node = q_node.front();
				q_node.pop();
				if (node->left) q_node.push(node->left);
				if (node->right) q_node.push(node->right);
			}
			dep++;
		}
		return dep;
	}


	// DFS实现二叉树的深度计算
	// 递归函数的功能是计算树的最大深度
	int tree_simple_avl::dfs(node_simple* root)
	{
		if (root == NULL)
			return 0;
		int l = dfs(root->left);
		int r = dfs(root->right);
		return max(l + 1, r + 1);
	}




	//tree_simple_avl2
	tree_simple_avl2::tree_simple_avl2()
	{
		m_root = NULL;
	}
	bool tree_simple_avl2::insert(BiTBode* node)
	{
		if (!node)
		{
			return true;
		}

		if (!m_root)
		{
			m_root = node;
			return true;
		}

		BiTBode* cur = m_root;

		while (1)
		{
			if (node->data == cur->data)
			{
				return false;
			}

			if (node->data < cur->data)
			{
				if (!(cur->lchild))
				{
					cur->lchild = node;
					return true;
				}
				else
				{
					cur = cur->lchild;
					continue;
				}
			}

			if (node->data > cur->data)
			{
				if (!(cur->rchild))
				{
					cur->rchild = node;
					return true;
				}
				else
				{
					cur = cur->rchild;
					continue;
				}
			}
		}

		return false;
	}

	bool tree_simple_avl2::insert(int node)
	{
		BiTBode* pnode = new BiTBode;
		pnode->data = node;
		pnode->lchild = NULL;
		pnode->rchild = NULL;

		if (insert(pnode))
		{
			return true;
		}

		delete pnode;		
		return false;
	}

	void tree_simple_avl2::print(BiTBode* node)
	{
		if (!node)
		{
			Traverse(m_root);
		}
		else
		{
			Traverse(node);
		}		
	}


	//// BFS实现二叉树的深度计算
	//int tree_simple_avl::bfs(node_simple* root)
	//{
	//	if (root == NULL) return 0;
	//	int dep = 0;
	//	std::queue<node_simple*> q_node;
	//	q_node.push(root);
	//	while (!q_node.empty())
	//	{
	//		int n_size = q_node.size();
	//		for (int i = 0; i < n_size; i++)
	//		{
	//			node_simple* node = q_node.front();
	//			q_node.pop();
	//			if (node->left) q_node.push(node->left);
	//			if (node->right) q_node.push(node->right);
	//		}
	//		dep++;
	//	}
	//	return dep;
	//}


	//// DFS实现二叉树的深度计算
	//// 递归函数的功能是计算树的最大深度
	//int tree_simple_avl::dfs(node_simple* root)
	//{
	//	if (root == NULL)
	//		return 0;
	//	int l = dfs(root->left);
	//	int r = dfs(root->right);
	//	return max(l + 1, r + 1);
	//}
}
