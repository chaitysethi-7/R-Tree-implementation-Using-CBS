#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define M 4
#define m 2

 typedef struct point {
    int x;//x coordinate
    int y;//y coordinate
 } Point;



typedef struct rectangle{   
    Point lowest; //Bottom left corner
    Point highest; //Top right corner
} Rectangle;



typedef struct Node
{
    int isleaf;                      // TO check whether the given node is a leaf or not
    int num_children;                // the number telling us how many children does the node has for leaf it will mean how many points
    struct Node *parent;             // the pointer pointing its parent
    Rectangle mbr;                   // Minimum bounded region of the present node
    struct Node* children[M];       // Stores to pointers to the children of the present node
    Point points[M];                // Stores the Index records i.e our coordinates. This is used by leaf nodes
} Node;



typedef struct rtree
{
    Node *root;                     // The root of rtree
} RTree;



//Function to calculate area of a given rectangle
int calculateArea(Rectangle r){
    int area = (r.highest.x-r.lowest.x)*(r.highest.y-r.lowest.y);
    return (area);
}



//It is a function to calculate a MBR for a given array of points 
Rectangle calculateMbrThroughPoints(Point pt[],int n){
    Rectangle r;
    int xmin = pt[0].x;
    int ymin = pt[0].y;
    int xmax = pt[0].x;
    int ymax = pt[0].y;
    for (int i = 0; i < n; i++)
    {
        if(pt[i].x>xmax){
            xmax = pt[i].x;
        }
        else if(pt[i].x<xmin){
            xmin = pt[i].x;
        }
        else{
            continue;
        }  
    }
    for (int i = 0; i < n; i++)
    {
        if(pt[i].y>ymax){
            ymax = pt[i].y;
        }
        else if(pt[i].y<ymin){
            ymin = pt[i].y;
        }
        else{
            continue;
        }  
    }
    r.lowest.x = xmin;
    r.lowest.y = ymin;
    r.highest.x = xmax;
    r.highest.y = ymax;
    return r;
}
int max(int n1,int n2){
    if(n1>n2){
        return(n1);
    }
    else{
        return(n2);
    }
}
int min(int n1,int n2){
    if(n1>n2){
        return n2;
    }
    else{
        return n1;
    }
}


// The minimum bounding Rectangle is calculated for a given Array Of nodes
Rectangle findMinimumBoundingRectangle(Node* node[], int numRectangles) {
    // Initialize the minimum bounding rectangle to the first rectangle in the array
    Rectangle minBoundingRect = node[0]->mbr;
    // Loop through the rest of the rectangles and adjust the minimum bounding rectangle as needed
    for (int i = 1; i < numRectangles; i++) {
        // Update the lowest point of the minimum bounding rectangle
        if (node[i]->mbr.lowest.x < minBoundingRect.lowest.x) {
            minBoundingRect.lowest.x = node[i]->mbr.lowest.x;
        }
        if (node[i]->mbr.lowest.y < minBoundingRect.lowest.y) {
            minBoundingRect.lowest.y = node[i]->mbr.lowest.y;
        }
        // Update the highest point of the minimum bounding rectangle
        if (node[i]->mbr.highest.x > minBoundingRect.highest.x) {
            minBoundingRect.highest.x = node[i]->mbr.highest.x;
        }
        if (node[i]->mbr.highest.y > minBoundingRect.highest.y) {
            minBoundingRect.highest.y = node[i]->mbr.highest.y;
        }
    }
    return minBoundingRect;
}



// It calculates the minimum MBR for a given array of rectangles
Rectangle RectMinimumBoundingRectangle(Rectangle node[], int numRectangles) {
    // Initialize the minimum bounding rectangle to the first rectangle in the array
    Rectangle minBoundingRect = node[0];
    // Loop through the rest of the rectangles and adjust the minimum bounding rectangle as needed
    for (int i = 1; i < numRectangles; i++) {
        // Update the lowest point of the minimum bounding rectangle
        if (node[i].lowest.x < minBoundingRect.lowest.x) {
            minBoundingRect.lowest.x = node[i].lowest.x;
        }
        if (node[i].lowest.y < minBoundingRect.lowest.y) {
            minBoundingRect.lowest.y = node[i].lowest.y;
        }
        // Update the highest point of the minimum bounding rectangle
        if (node[i].highest.x > minBoundingRect.highest.x) {
            minBoundingRect.highest.x = node[i].highest.x;
        }
        if (node[i].highest.y > minBoundingRect.highest.y) {
            minBoundingRect.highest.y = node[i].highest.y;
        }
    }
    return minBoundingRect;
}



// Function for printing the MBR coordinates (Highest and Lowest of the given rectangle)
void printMBR(Rectangle mbr){
    printf("(%d,%d);(%d,%d)\n",mbr.highest.x, mbr.highest.y, mbr.lowest.x, mbr.lowest.y);
}


//Function for calculating the Pre-Order Traversal of the given Node alongwith printing the MBR Coordinates
//This is Recursive in nature and will be invoked by preOrderOfTree().
void preOrder(Node *node)
{

    if (node->isleaf == 1)
    {
        printMBR(node->mbr);        
        return;                     // Return upon encountering a leaf Node and prints its MBR by invoking printMBR()
    }
    else{
    printMBR(node->mbr);
    for (int i = 0; i < node->num_children; i++)
    {
        //printMBR(node->mbr);
        preOrder(node->children[i]);        // Recursively calling all children of the current Node
    }
    }
}



//Function for calculating the Pre-Order Traversal of the given R-Tree alongwith printing the MBR Coordinates
void preOrderOfTree(RTree *rtree){
    preOrder(rtree->root);
}



// This is a function to calculate the resulting mbr when a child rectangle is added
Rectangle newMbrOfParentNode(Rectangle parent,Rectangle child){
    
    int xmin,xmax,ymin,ymax;
    if(parent.lowest.x>=child.lowest.x){
        xmin = child.lowest.x;
    }
    else{                                       // This sets the xmin of the final rectangle
        xmin = parent.lowest.x;
    }
    if(parent.lowest.y>=child.lowest.y){
        ymin = child.lowest.y;
    }
    else{                                   // This sets the ymin of the final rectangle
        ymin = parent.lowest.y; 
    }
    if(parent.highest.x>=child.highest.x){
        xmax = parent.highest.x; 
    }
    else{                                       // This sets the xmax of the final rectangle
        xmax = child.highest.x;
    }
    if(parent.highest.y>=child.highest.y){
        ymax = parent.highest.y;
    }
    else{                                       // This sets the ymax of the final rectangle
        ymax = child.highest.y;
    }
    Rectangle r;
    r.highest.x = xmax;
    r.highest.y = ymax;
    r.lowest.x = xmin;
    r.lowest.y = ymin;
    return(r);                              // The new Rectangle is Returned.
}



// This function is to create a new Node using the parameters entered by dynamically allocating memory.
Node* createNode(Point highest,Point lowest,int isleaf){
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->parent = NULL;
    newNode->num_children = 0;
    newNode->isleaf = isleaf;               
    Rectangle r;
    r.highest = highest;                      //The Point parameters are corresponding to the
    r.lowest = lowest;                        //node’s highest point and node’s lowest point for defining a MBR(rectangle ‘r’). 
    newNode->mbr = r;
    newNode->points[4];                     // Allocating Memory to Points of new Node.
    for(int i = 0;i<4;i++){
            newNode->children[i] = (Node*)malloc(sizeof(Node));         //Allocating memory to children of new node.
        }
    return newNode;
}



//This is a function to create rtree
RTree* createRtree(Point highest, Point lowest){

    RTree* rtree = (RTree *)malloc(sizeof(RTree));      // Allocating memory to the RTree structure.
    Node * temp = createNode(highest,lowest,1);         // Defining the root node for this RTree as a Leaf Node.
    rtree->root = temp;
    return rtree;                                       //Returning the RTree Pointer.
}



//This function is made to update the MBR of all the ancestors from the current Node(i.e. 'node')
void AdjustMbr(Node* node){
    Node* new = (Node*)malloc(sizeof(Node));
    new = node;
    while(new->parent!=NULL){
        new->parent->mbr = newMbrOfParentNode(new->parent->mbr,new->mbr);  // Updating the MBR of the current node's parent 
        new = new->parent;                                                 // Setting the current node to its parent node
    }
}



// This function Checks if a Rectangle(ele) is completely lying inside of another Rectangle(r) or not
bool contains(Rectangle r,Rectangle ele){
    if((ele.lowest.x >= r.lowest.x) && (ele.lowest.y >= r.lowest.y) &&(ele.highest.x<= r.highest.x) &&(ele.highest.y<= r.highest.y))
    {
                return true;                //Returned if 'ele' lies completely inside of 'r'
    }
    else{

        return false;
    }
}



//This function checks whether ele intersects with r or not
bool intersects(Rectangle r,Rectangle ele){
    return(ele.highest.x >= r.lowest.x &&
            ele.lowest.x <= r.highest.x&&           //Returns True if Intersecting by the condition Provided else returns False
            ele.highest.y >= r.lowest.y&&
            ele.lowest.y <= r.highest.y);
}



//This function is used to insert points into a leaf node
void insertPointIntoLeaf(Node* node,Point pt[],int n){              
    for(int i = 0;i<n;i++){                                                 //Inserting points into the leaf Node('node')
        node->points[node->num_children] = pt[i];
        node->num_children++;
    }
    Rectangle r;
    r = calculateMbrThroughPoints(node->points,node->num_children);         //Updating the MBR of the given Node (node)
    node->mbr = r;
}



// This function is Takes 3 Parameters and inserts Children nodes into current Node('node')
void insertChildIntoNode(Node* node,Node* child[],int n){
    for(int i = 0;i<n;i++){                                                //inserts Children nodes into current Node('node') 
        node->children[node->num_children] = child[i];
        node->num_children++;
        child[i]->parent = node;
    }
    Rectangle r;
    r = findMinimumBoundingRectangle(node->children,node->num_children);    //Updating the MBR of the given Node (node)
    node->mbr = r;
}



// This function calculates the overlapping between the 2 rectangle 'rect1' and 'rect2'
int overlap_area(Rectangle rect1, Rectangle rect2) {
    // Determine the coordinates of the overlapping rectangle
    int x1 = max(rect1.lowest.x, rect2.lowest.x);
    int y1 = max(rect1.lowest.y, rect2.lowest.y);
    int x2 = min(rect1.highest.x, rect2.highest.x);
    int y2 = min(rect1.highest.y, rect2.highest.y);
    // Calculate the width and height of the overlapping rectangle
    int width = max(0, x2 - x1);
    int height = max(0, y2 - y1);

    // Calculate the area of the overlapping rectangle
    int area = width * height;
    return area;
}



//This function is used to Search and print those leaf nodes where the Rectangle 'r' is intersecting with its MBR
// This function is the search function mentioned in paper
void searching(Node* child,Rectangle r){
    if (intersects(child->mbr,r)||contains(child->mbr,r)){
        if(child->isleaf){
            printMBR(child->mbr);
        }
        else{
            for(int i =0;i<child->num_children;i++){
                    searching(child->children[i], r);
                }
            }
        }
}



// This function is udsed to calculate the Area of MBR increase upon insertion of the point 'p' into the Rectangle 'r'
int calculateEnlargement(Rectangle r,Point p){
    int old_area = calculateArea(r);
    int new_area;
    Rectangle r1;
    Rectangle r2;
    r1.highest.x = p.x;
    r1.highest.y = p.y;
    r1.lowest.x = p.x;
    r1.lowest.y = p.y;
    r2 = newMbrOfParentNode(r,r1);
    new_area = calculateArea(r2);
    return(new_area-old_area);
}


//This function is used as intermiediate function in insertion and chooses the idea leaf node where the point 'p' should be inserted
// The algorithm for choosing this leaf follows minimum Area Enlargement of MBR and if Area Enlargement is same, The MBR with lower area is considered
Node* ChooseLeaf(Node* node,Point p){
    int area1;
    int area2;
    int n = 0;
    if(node->isleaf == 1){
        return node;
    }
    int min_enlargement = calculateEnlargement(node->children[0]->mbr,p);       // Minimum enlargement in Area is calculated for a given node
    Node* choosen_child = node->children[0];
    for(int i =0;i<node->num_children;i++){
        int curr_enlargement = calculateEnlargement(node->children[i]->mbr,p);
        if(curr_enlargement<min_enlargement){
            n = i;
            min_enlargement =curr_enlargement;
            choosen_child = node->children[i];
        }
        else if(curr_enlargement==min_enlargement){
            area1 = calculateArea(node->children[i]->mbr);
            area2 = calculateArea(node->children[n]->mbr);
            if(area2 > area1){
                min_enlargement = curr_enlargement;
                n = i;
                choosen_child = node->children[i];
            }
            else{
                continue;
            }
        }
        else{
            continue;
        }
    }
    return ChooseLeaf(choosen_child,p);     // Recursively call for the child of the given Node with minimum area enlargement.
}



// This function is used to implement Corner Based Splitting where node 1 is the parent node and node 2 is the one which needs to be added to the parent node 
//after being inserted as a child and to decide on which axis the overflown node should be split into two new nodes.
// Here node 1 is the main node and node 2 is the one which needs to be added to the children
Node* CBSNodes(Node* node1,Node* node2){
    float xcen,ycen;                                        // Centre of our parent node MBRs (Rectangles)
    float xobjcen,yobjcen;                                  //Centre of the child MBRs (Rectangles)
    node1->mbr=newMbrOfParentNode(node1->mbr,node2->mbr);


    //We define another Nodes pointer array to store all the 5 childs available to us
    Node* childs[5];
    for (size_t i = 0; i < 5; i++)
    {
        childs[i] = (Node*)malloc(sizeof(Node));
    }
    for (size_t i = 0; i < 4; i++)
    {
        childs[i] = node1->children[i];
    }


    childs[4] = node2;// Till here we have stored all the 5 childs
    //Counters for our corners

    //We define a counter for each corner, calculate the centre of each entry (object) in node N,
    //record the object with the nearest corner by incrementing that corner’s counter.
    int c0 = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;

    //Creating dynamic arrays to store the exact indexes for the specific childs
    //which can be later used to access those specific child nodes
    int C0[5];
    int C1[5];
    int C2[5];
    int C3[5];
    xcen = ((float)node1->mbr.highest.x+(float)node1->mbr.lowest.x)/2;
    ycen = ((float)node1->mbr.highest.y+(float)node1->mbr.lowest.y)/2;

    // Now we compare the centre coordinates of the MBRs of our children nodes with centre coordinates of 
    // parent node MBR so as to divide the MBRs into quadrants as per the nearest Corners 
    // and incrementing counters accordingly
    for (int i = 0;i<5;i++){
        xobjcen = ((float)childs[i]->mbr.highest.x+(float)childs[i]->mbr.lowest.x)/2;
        yobjcen = ((float)childs[i]->mbr.highest.y+(float)childs[i]->mbr.lowest.y)/2;
        if(xobjcen>xcen){
            if(yobjcen>ycen){
                C2[c2] = i;
                c2++;               //incrementing counter
            }
            else{
                C3[c3] = i;
                c3++;               //incrementing counter
            }
        }
        else{
            if(yobjcen>ycen){
                C1[c1] = i;
                c1++;               //incrementing counter
            }
            else{
                C0[c0] = i;
                c0++;               //incrementing counter
            }   
        }
    }

    //Creating two new nodes N1,N2 to store the children split based on
    //We Create dynamic arrays to store the exact indices for the specific “childs” which are used later to access those specific child nodes
    //via the Point arrays mentioned below.
    Point hi,low;
    hi.x = node1->mbr.highest.x;
    low.x = node1->mbr.lowest.x;
    hi.y = node1->mbr.highest.y;
    low.y = node1->mbr.lowest.y;
    Node* N1 = createNode(hi,low,0);    
    Node* N2 = createNode(hi,low,0);
    int pt1 = 0;
    int pt2 = 0; 
    Node* PT1[5];
    Node* PT2[5];

    //We check if the node is a root node or a non-root node as the splitted nodes later need to be assigned parents which won’t take place in root node

    if (node1->parent==NULL)
    {
        if(c0>c2){
            for (int i = 0; i < c0; i++)
            {
                PT1[pt1] = childs[C0[i]];
                pt1++;
            }
            for (int i = 0; i < c2; i++)
            {
                PT2[pt2] = childs[C2[i]];
                pt2++;
            }        
        }
        else{
            for (int i = 0; i < c2; i++)
            {
                PT1[pt1] = childs[C2[i]];
                pt1++;
            }
            for (int i = 0; i < c0; i++)
            {
                PT2[pt2] = childs[C0[i]];
                pt2++;
            }
        }
        if(c1>c3){
            for (int i = 0; i < c1; i++)
            {
                PT2[pt2] = childs[C1[i]];
                pt2++;
            }
            for (int i = 0; i < c3; i++)
            {
                PT1[pt1] = childs[C3[i]];
                pt1++;
            }
        }
        else if(c3>c1){
                for (int i = 0; i < c3; i++)
                {
                    PT2[pt2] = childs[C3[i]];
                    pt2++;
                }
                for (int i = 0; i < c1; i++)
                {
                    PT1[pt1] = childs[C1[i]];
                    pt1++;
                }  
        }
        //We have also considered the Tie-breaker case of c1 = c3 where We try both the combinations of c0 with c3; c2 with c1 and c0 with c1; c2 with c
        //and choose the correct based on minimum area enlargement.
        //This is ensured by using the Rectangle structures for storing temporarily the MBRs using RectMinimumBoundingRectangle()
        //and then calculating the area using calculateArea() for R1, R2, R3 and R4 whose respective sum is minimized as considered from the two cases mentioned above.
        else{                           
            Rectangle RT1[5];
            Rectangle RT2[5];
            Rectangle RT3[5];
            Rectangle RT4[5];
            int nr1 = pt1;
            int nr2 = pt2;
            int nr3 = pt1;
            int nr4 = pt2;
            Rectangle R4;
            Rectangle R1;
            Rectangle R2;
            Rectangle R3;
            int Rarea1;
            int Rarea2;
            int Rarea3;
            int Rarea4;
            for(int i= 0;i<nr1;i++){
                RT1[i] = PT1[i]->mbr;
            }
            for (int i = 0; i < c1; i++)
            {
                RT1[nr1] = childs[C1[i]]->mbr;
                nr1++;
            }
            for(int i= 0;i<nr2;i++){
                RT2[i] = PT2[i]->mbr;
            }
            for (int i = 0; i < c3; i++)
            {
                RT2[nr1] = childs[C3[i]]->mbr;
                nr2++;
            }
            R1 = RectMinimumBoundingRectangle(RT1,nr1);
            R2 = RectMinimumBoundingRectangle(RT2,nr2);
            for(int i= 0;i<nr3;i++){
                RT3[i] = PT1[i]->mbr;
            }
            for (int i = 0; i < c3; i++)
            {
                RT3[nr3] = childs[C3[i]]->mbr;
                nr3++;
            }
            for(int i= 0;i<nr4;i++){
                RT4[i] = PT2[i]->mbr;
            }
            for (int i = 0; i < c1; i++)
            {
                RT4[nr4] = childs[C1[i]]->mbr;
                nr4++;
            }
            R3 = RectMinimumBoundingRectangle(RT3,nr3);
            R4 = RectMinimumBoundingRectangle(RT4,nr4);
            Rarea1 = calculateArea(R1);
            Rarea2 = calculateArea(R2);
            Rarea3 = calculateArea(R3);
            Rarea4 = calculateArea(R4);
            if((Rarea1+Rarea2)<(Rarea3+Rarea4)){
                for (int i = 0; i < c3; i++)
                {
                    PT1[pt1] = childs[C3[i]];
                    pt1++;
                }
                for (int i = 0; i < c1; i++)
                {
                    PT2[pt2] = childs[C1[i]];
                    pt2++;
                }
            }
            else{
                for (int i = 0; i < c1; i++)
                {
                    PT1[pt1] = childs[C1[i]];
                    pt1++;
                }
                for (int i = 0; i < c3; i++)
                {
                    PT2[pt2] = childs[C3[i]];
                    pt2++;
                }
            }
        }
        insertChildIntoNode(N1,PT1,pt1);  
        insertChildIntoNode(N2,PT2,pt2);
        for (int i = 0; i < 4; i++)
        {
            node1->children[i]=NULL;
        }
        N1->parent = node1;
        N2->parent = node1;
        node1->children[0] = N1;
        node1->children[1] = N2;
        node1->num_children = 2;
        node1->mbr = newMbrOfParentNode(node1->mbr,N1->mbr);
        node1->mbr = newMbrOfParentNode(node1->mbr,N2->mbr);
        return NULL;
    }
    else{
        if(c0>c2){
            for (int i = 0; i < c0; i++)
            {
                PT1[pt1] = childs[C0[i]];
                pt1++;
            }
            for (int i = 0; i < c2; i++)
            {
                PT2[pt2] = childs[C2[i]];
                pt2++;
            }        
        }
        else{
            for (int i = 0; i < c2; i++)
            {
                PT1[pt1] = childs[C2[i]];
                pt1++;
            }
            for (int i = 0; i < c0; i++)
            {
                PT2[pt2] = childs[C0[i]];
                pt2++;
            }
        }
        if(c1>c3){
            for (int i = 0; i < c1; i++)
            {
                PT2[pt2] = childs[C1[i]];
                pt2++;
            }
            for (int i = 0; i < c3; i++)
            {
                PT1[pt1] = childs[C3[i]];
                pt1++;
            }
        }
        else if(c3>c1){
                for (int i = 0; i < c3; i++)
                {
                    PT2[pt2] = childs[C3[i]];
                    pt2++;
                }
                for (int i = 0; i < c1; i++)
                {
                    PT1[pt1] = childs[C1[i]];
                    pt1++;
                }  
        }
        else{
            Rectangle RT1[5];
            Rectangle RT2[5];
            Rectangle RT3[5];
            Rectangle RT4[5];
            int nr1 = pt1;
            int nr2 = pt2;
            int nr3 = pt1;
            int nr4 = pt2;
            Rectangle R4;
            Rectangle R1;
            Rectangle R2;
            Rectangle R3;
            int Rarea1;
            int Rarea2;
            int Rarea3;
            int Rarea4;
            for(int i= 0;i<nr1;i++){
                RT1[i] = PT1[i]->mbr;
            }
            for (int i = 0; i < c1; i++)
            {
                RT1[nr1] = childs[C1[i]]->mbr;
                nr1++;
            }
            for(int i= 0;i<nr2;i++){
                RT2[i] = PT2[i]->mbr;
            }
            for (int i = 0; i < c3; i++)
            {
                RT2[nr1] = childs[C3[i]]->mbr;
                nr2++;
            }
            R1 = RectMinimumBoundingRectangle(RT1,nr1);
            R2 = RectMinimumBoundingRectangle(RT2,nr2);
            for(int i= 0;i<nr3;i++){
                RT3[i] = PT1[i]->mbr;
            }
            for (int i = 0; i < c3; i++)
            {
                RT3[nr3] = childs[C3[i]]->mbr;
                nr3++;
            }
            for(int i= 0;i<nr4;i++){
                RT4[i] = PT2[i]->mbr;
            }
            for (int i = 0; i < c1; i++)
            {
                RT4[nr4] = childs[C1[i]]->mbr;
                nr4++;
            }
            R3 = RectMinimumBoundingRectangle(RT3,nr3);
            R4 = RectMinimumBoundingRectangle(RT4,nr4);
            Rarea1 = calculateArea(R1);
            Rarea2 = calculateArea(R2);
            Rarea3 = calculateArea(R3);
            Rarea4 = calculateArea(R4);
            if((Rarea1+Rarea2)<(Rarea3+Rarea4)){
                for (int i = 0; i < c3; i++)
                {
                    PT1[pt1] = childs[C3[i]];
                    pt1++;
                }
                for (int i = 0; i < c1; i++)
                {
                    PT2[pt2] = childs[C1[i]];
                    pt2++;
                }
            }
            else{
                for (int i = 0; i < c1; i++)
                {
                    PT1[pt1] = childs[C1[i]];
                    pt1++;
                }
                for (int i = 0; i < c3; i++)
                {
                    PT2[pt2] = childs[C3[i]];
                    pt2++;
                }
            }
        }
        node1->num_children = 0;
        insertChildIntoNode(node1,PT1,pt1);  // Inserting split child into the old node
        insertChildIntoNode(N2,PT2,pt2);    // Imsertimg the split Child into new node
        return(N2);
    }
}





//This is used to implement Corner Based Splitting Algorithm at the leaf node
//where if a node is already housing 4 points in it and we want to add one more point in the leaf node then CBSPoint() is called.
Node* CBSPoint(Node* node,Point p){
    if(node->isleaf){
        float xcen,ycen;                // centre of the 'node' MBR
        Rectangle r;
        r.highest.x=p.x;
        r.lowest.y=p.y;
        r.lowest.x=p.x;
        r.lowest.y=p.y;
        node->mbr = newMbrOfParentNode(node->mbr,r);
        Point childs[5];
        for (size_t i = 0; i < 4; i++)
        {
            childs[i] = node->points[i];
        }

        childs[4] = p;// Till here we have stored all the 5 childs
        //Counters for our corners
        int c0 = 0;
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        int C0[5];
        int C1[5];
        int C2[5];
        int C3[5];
        xcen = ((float)node->mbr.highest.x+(float)node->mbr.lowest.x)/2;
        ycen = ((float)node->mbr.highest.y+(float)node->mbr.lowest.y)/2;
    // Now we compare the centre coordinates of the MBRs of our children nodes with centre coordinates of 
    // parent node MBR so as to divide the MBRs into quadrants as per the nearest Corners 
    // and incrementing counters accordingly
        for (int i = 0; i < 5; i++)
        {
            if(childs[i].x>xcen){
                if(childs[i].y>ycen){
                    C2[c2] = i;
                    c2++;
                }
                else{
                    C3[c3] = i;
                    c3++;
                }
            }
            else{
                if(childs[i].y>ycen){
                    C1[c1] = i;
                    c1++;
                }
                else{
                    C0[c0] = i;
                    c0++;
                }
            }
        }

//Creating two new nodes N1,N2 to store the children split based on
//We Create dynamic arrays to store the exact indices for the specific “childs” which are used later to access those specific child nodes
//via the Point arrays mentioned below.
        Point hi,low;
        hi.x = node->mbr.highest.x;
        low.x = node->mbr.lowest.x;
        hi.y = node->mbr.highest.y;
        low.y = node->mbr.lowest.y;
        Node* N1 = createNode(hi,low,1);
        Node* N2 = createNode(hi,low,1);
        int pt1=0;
        int pt2=0;
        Point PT1[5];
        Point PT2[5];


        if(c0>c2){
            for (int i = 0; i < c0; i++)
            {
                PT1[pt1] = childs[C0[i]];
                pt1++;
            }
            for (int i = 0; i < c2; i++)
            {
                PT2[pt2] = childs[C2[i]];
                pt2++;
            }        
        }
        else{
            for (int i = 0; i < c2; i++)
            {
                PT1[pt1] = childs[C2[i]];
                pt1++;
            }
            for (int i = 0; i < c0; i++)
            {
                PT2[pt2] = childs[C0[i]];
                pt2++;
            }
        }
        if(c1>c3){
            for (int i = 0; i < c1; i++)
            {
                PT2[pt2] = childs[C1[i]];
                pt2++;
            }
            for (int i = 0; i < c3; i++)
            {
                PT1[pt1] = childs[C3[i]];
                pt1++;
            }
        }
        else if(c3>c1){
                for (int i = 0; i < c3; i++)
                {
                    PT2[pt2] = childs[C3[i]];
                    pt2++;
                }
                for (int i = 0; i < c1; i++)
                {
                    PT1[pt1] = childs[C1[i]];
                    pt1++;
                }  
        }
        //We have also considered the Tie-breaker case of c1 = c3 where We try both the combinations of c0 with c3; c2 with c1 and c0 with c1; c2 with c
        //and choose the correct based on minimum area enlargement.
        //This is ensured by using the Rectangle structures for storing temporarily the MBRs using RectMinimumBoundingRectangle()
        //and then calculating the area using calculateArea() for R1, R2, R3 and R4 whose respective sum is minimized as considered from the two cases mentioned above.                                  
        else{
            Rectangle R4;
            Rectangle R1;
            Rectangle R2;
            Rectangle R3;
            int Rarea1;
            int Rarea2;
            int Rarea3;
            int Rarea4;
            int nr1 = pt1;
            int nr2 = pt2;
            int nr3 = pt1;
            int nr4 = pt2;
            Point RPT1[5];
            Point RPT2[5];
            Point RPT3[5];
            Point RPT4[5];
            for(int i= 0;i<nr1;i++){
                RPT1[i] = PT1[i];
            }
            for (int i = 0; i < c1; i++)
            {
                RPT1[nr1] = childs[C1[i]];
                nr1++;
            }
            for(int i= 0;i<nr2;i++){
                RPT2[i] = PT2[i];
            }
            for (int i = 0; i < c3; i++)
            {
                RPT2[nr1] = childs[C3[i]];
                nr2++;
            }
            R1 = calculateMbrThroughPoints(RPT1,nr1);
            R2 = calculateMbrThroughPoints(RPT2,nr2);
            for(int i= 0;i<nr3;i++){
                RPT3[i] = PT1[i];
            }
            for (int i = 0; i < c3; i++)
            {
                RPT3[nr3] = childs[C3[i]];
                nr3++;
            }
            for(int i= 0;i<nr4;i++){
                RPT4[i] = PT2[i];
            }
            for (int i = 0; i < c1; i++)
            {
                RPT4[nr4] = childs[C1[i]];
                nr4++;
            }
            R3 = calculateMbrThroughPoints(RPT3,nr3);
            R4 = calculateMbrThroughPoints(RPT4,nr4);
            Rarea1 = calculateArea(R1);
            Rarea2 = calculateArea(R2);
            Rarea3 = calculateArea(R3);
            Rarea4 = calculateArea(R4);
            if((Rarea1+Rarea2)<(Rarea3+Rarea4)){
                for (int i = 0; i < c3; i++)
                {
                    PT1[pt1] = childs[C3[i]];
                    pt1++;
                }
                for (int i = 0; i < c1; i++)
                {
                    PT2[pt2] = childs[C1[i]];
                    pt2++;
                }
            }
            else{
                for (int i = 0; i < c1; i++)
                {
                    PT1[pt1] = childs[C1[i]];
                    pt1++;
                }
                for (int i = 0; i < c3; i++)
                {
                    PT2[pt2] = childs[C3[i]];
                    pt2++;
                }
            }
        }
        if(node->parent==NULL){
            insertPointIntoLeaf(N1,PT1,pt1);
            insertPointIntoLeaf(N2,PT2,pt2);
            node->isleaf=0;
            N1->parent=node;
            N2->parent=node;
            node->children[0] = N1;
            node->children[1] = N2;
            node->num_children =2;
            node->mbr=newMbrOfParentNode(node->mbr,N1->mbr);
            node->mbr=newMbrOfParentNode(node->mbr,N2->mbr);
            return NULL;
        }
        else{
            node->num_children = 0;
            insertPointIntoLeaf(node,PT1,pt1);
            insertPointIntoLeaf(N2,PT2,pt2);
            return(N2);
        }
    }
    else{
        printf("You haven't provided leaf node for entering points");
    }
}



//This function is used after CBS nodes and is used to check wether the parent of node inserted by CBS nodes excceds max capacity or not
//If it does then adjust tree splits the parent node and calls recursively for its parent too 
void AdjustTree(Node* node,Node* child){
    if(node==NULL){
        return;
    }
    else if(child!=NULL && node->num_children <M){
        insertChildIntoNode(node,&child,1);
    }
    else if(node->num_children>=M){
        Node* newNode = (Node*)malloc(sizeof(Node));
        if(node->parent==NULL){
            newNode = CBSNodes(node,child);
            return;
        }
        else{
            newNode = CBSNodes(node,child);
            newNode->parent = node->parent;
            AdjustTree(node->parent,newNode);
        }
    }
}


//This function in responsible for inserting point into our tree. It calls other sub-functions to complete insertion.
RTree* insertion(RTree* temp,Point p){
    Node* node = (Node*)malloc(sizeof(Node));
    node = ChooseLeaf(temp->root,p);                    //Choose-leaf called and it returns the ideal leaf node to insert the points
    if(node->num_children<M){                               
        insertPointIntoLeaf(node,&p,1);                 // If leaf node has space to insert the point its is inserted by calling insertpointintoleaf
        AdjustMbr(node);                                    //MBR of parent nodes are adjusted 
    }
    else if(node->num_children>=M){                         //If we don't have space in the leaf node we call for CBSpoint and then Adjust tree
        Node* split_node = (Node*)malloc(sizeof(Node));
        split_node = CBSPoint(node,p);
        AdjustTree(node->parent,split_node);
        AdjustMbr(node);
    }
    return temp;
}


//The main function , it inserts sample data into our code and is responsible for output
int main(){
    RTree* temp;
    Point hi;
    Point low;
    hi.x = 0;
    hi.y = 0;
    low.x = 0;
    low.y = 0;
    temp = createRtree(hi,low);
    Point arr[21];
    FILE *fp;                                                           //opening file
    fp = fopen("data.txt", "r");
    int count = 0;
    int x1;
    int y1;
    if (fp == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Read in coordinate pairs until end of file or maximum size is reached
    while (fscanf(fp, "%d %d", &x1, &y1) != EOF && count < 21)                  //reading data
    {
        arr[count].x = x1;
        arr[count].y = y1;
        count++;
    }
    for (int i = 0; i < 21; i++)
    {
        printf("%d %d\n", arr[i].x, arr[i].y);                       //storing data in an array of points
    }
    fclose(fp);
    for (int i = 0; i < 21; i++)
    {
        Point p = arr[i];
        temp = insertion(temp,p);                                          //inserting data in our r tree
    }
    printf("Coordinates of Root node hi mbr: %d %d\n",temp->root->mbr.highest.x,temp->root->mbr.highest.y);
    printf("Coordinates of Root node lo mbr: %d %d\n",temp->root->mbr.lowest.x,temp->root->mbr.lowest.y);
    printf("Children of root are: %d\n",temp->root->num_children);
    printf("Node N1 coord hi: %d %d\n",temp->root->children[0]->mbr.highest.x,temp->root->children[0]->mbr.highest.y);
    printf("Node N1 coord lo: %d %d\n",temp->root->children[0]->mbr.lowest.x,temp->root->children[0]->mbr.lowest.y);
    printf("Node N2 coord hi: %d %d\n",temp->root->children[1]->mbr.highest.x,temp->root->children[1]->mbr.highest.y);
    printf("Node N2 coord lo: %d %d\n",temp->root->children[1]->mbr.lowest.x,temp->root->children[1]->mbr.lowest.y);
    // printf("Node N3 coord hi: %d %d\n",temp->root->children[2]->mbr.highest.x,temp->root->children[2]->mbr.highest.y);
    // printf("Node N3 coord lo: %d %d\n",temp->root->children[2]->mbr.lowest.x,temp->root->children[2]->mbr.lowest.y);
    // printf("Node N4 coord hi: %d %d\n",temp->root->children[3]->mbr.highest.x,temp->root->children[3]->mbr.highest.y);
    // printf("Node N4 coord lo: %d %d\n",temp->root->children[3]->mbr.lowest.x,temp->root->children[3]->mbr.lowest.y);
    // printf("Points in N4 1st: %d %d\n",temp->root->children[3]->points[0].x,temp->root->children[3]->points[0].y);
    // printf("Points in N4 2st: %d %d\n",temp->root->children[3]->points[2].x,temp->root->children[3]->points[1].y);
    // printf("Points in N4 3st: %d %d\n",temp->root->children[3]->points[1].x,temp->root->children[3]->points[2].y);
    printf("Node N1 number of children: %d\n",temp->root->children[0]->num_children);
    printf("Node N2 number of children: %d\n",temp->root->children[1]->num_children);

    preOrderOfTree(temp);
    Rectangle* searchingMbr = calloc(1,sizeof(Rectangle));
    int n = 1;
    Rectangle R12;
    R12.lowest.x =1;
    R12.lowest.y =15;
    R12.highest.x =20;
    R12.highest.y =19;
    printf("The intersecting nodes are: ");
    searching(temp->root,R12);                                  //This is the search function used to search for reactangle r2
    // int bd = sizeof(searchingMbr)/sizeof(searchingMbr[0]);
    // for (int i = 0; i < bd; i++)
    // {
    //     printf("intersecting mbr coord hi: %d %d\n",searchingMbr->highest.x,searchingMbr->highest.y);
    //     printf("intersecting mbr coord lo: %d %d\n",searchingMbr->lowest.x,searchingMbr->lowest.y);
    // }
    
    // printf("Node N3 number of children: %d\n",temp->root->children[2]->num_children);
    // printf("Node N4 number of children: %d\n",temp->root->children[3]->num_children);

    // printf("Node root-N2-1child hi coord: %d %d\n",temp->root->children[1]->children[0]->mbr.highest.x,temp->root->children[1]->children[0]->mbr.highest.y);
    // printf("Node root-N2-1child hi coord: %d %d\n",temp->root->children[1]->children[0]->mbr.lowest.x,temp->root->children[1]->children[0]->mbr.lowest.y);
    // printf("Node root-N2-1childrenum: %d\n",temp->root->children[1]->children[0]->num_children);
    // printf("Node root-N2-2child hi coord: %d %d\n",temp->root->children[1]->children[1]->mbr.highest.x,temp->root->children[1]->children[1]->mbr.highest.y);
    // printf("Node root-N2-2child hi coord: %d %d\n",temp->root->children[1]->children[1]->mbr.lowest.x,temp->root->children[1]->children[1]->mbr.lowest.y);
    // printf("Node root-N2-2childrenum: %d\n",temp->root->children[1]->children[1]->num_children);
    // printf("Node root-N2-3child hi coord: %d %d\n",temp->root->children[1]->children[2]->mbr.highest.x,temp->root->children[1]->children[2]->mbr.highest.y);
    // printf("Node root-N2-3child hi coord: %d %d\n",temp->root->children[1]->children[2]->mbr.lowest.x,temp->root->children[1]->children[2]->mbr.lowest.y);
    // printf("Node root-N2-3childrenum: %d\n",temp->root->children[1]->children[2]->num_children);
    // printf("Node root-N2-4child hi coord: %d %d\n",temp->root->children[1]->children[3]->mbr.highest.x,temp->root->children[1]->children[3]->mbr.highest.y);
    // printf("Node root-N2-4child hi coord: %d %d\n",temp->root->children[1]->children[3]->mbr.lowest.x,temp->root->children[1]->children[3]->mbr.lowest.y);
    // printf("Node root-N2-4childrenum: %d\n",temp->root->children[1]->children[3]->num_children);

    // printf("Node N3 number of children: %d\n",temp->root->children[2]->num_children);
    // printf("Node N4 number of children: %d\n",temp->root->children[3]->num_children);

    // printf("Root-N1-1child hi coord: %d %d\n",temp->root->children[0]->children[0]->mbr.highest.x,temp->root->children[0]->children[0]->mbr.highest.y);
    // printf("Roor-N1-1child-lo coord: %d %d\n",temp->root->children[0]->children[0]->mbr.lowest.x,temp->root->children[0]->children[0]->mbr.lowest.y);
    // printf("Root-N2-1child hi coord: %d %d\n",temp->root->children[0]->children[1]->mbr.highest.x,temp->root->children[0]->children[1]->mbr.highest.y);
    // printf("Roor-N2-1child-lo coord: %d %d\n",temp->root->children[0]->children[1]->mbr.lowest.x,temp->root->children[0]->children[1]->mbr.lowest.y);
    // printf("Root-N3-1child hi coord: %d %d\n",temp->root->children[0]->children[2]->mbr.highest.x,temp->root->children[0]->children[2]->mbr.highest.y);
    // printf("Roor-N3-1child-lo coord: %d %d\n",temp->root->children[0]->children[2]->mbr.lowest.x,temp->root->children[0]->children[2]->mbr.lowest.y);
}

