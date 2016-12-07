#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

static int  x ;


class coder {
     public:

     int x ;     
     coder()
     {
	printf( "coder constructor - %x\n", x );
        x = 0 ;
     } ;
     ~coder() 
     {
        //printf( "coder destructor\n");
     } ;
     int incr() 
     {
          ++x ;
          cout << "coder->x - " << x << "\n" ;
          return x ;
     }
 
} ;



class listNode {
     public:
     listNode *next ;
     listNode *prev ;
     listNode *head ;

     listNode(){
     	next = NULL ;
        prev = NULL ;
        head = NULL ;
        genTime = 0L ;  
     } 

     // for the moment, this is the data payload.
     time_t genTime ;

} ;

class linkedList {
     public:
     linkedList()
     {
          head = NULL ;
          tail = NULL ;
          linkLastTime = 0L ;
          nodeCount = 0 ;
     } ;
     ~linkedList()
     {

     } ;

     int addNodeAtEnd(time_t addTime)
     { 
          listNode *node = new listNode ;
          if( node == NULL ) 
          {
               return 0 ;
          }  

          cout << "Add time - " << addTime << "\n" ;
          if( head == NULL) 
          {
               // top and only in the list
               head = node ;
               tail = node ;
               node->head = node ;
               node->genTime = addTime ;
          }
          else 
          {
               // else, add this node to the end of the list.               
	       node->head    = head ;
               node->prev    = tail ;
               node->genTime = addTime ;

               tail->next = node ;
               tail       = node ;
              
          }
          nodeCount++ ;
          linkLastTime = addTime ;
         
          cout << "Add time - " << addTime << " (count-" << nodeCount << ")\n" ;
          return nodeCount ;
          
     } ;

     int dumpListFromTop()
     { 
          listNode *node = head ;
          if( node == NULL ) 
          {
               cout << "List is empty.\n" ;
          }
          else 
          {
               cout << "\nDump list from top - \n" ;
               while( node != NULL) 
               {
                    cout << "     Add time - " << node->genTime << " (count-" << nodeCount << ")\n" ;
                    node = node->next ;
               }
          }
          
          return nodeCount ;
     } ;


     int freeListFromTop()
     { 
          listNode *node = head ;
          if( node == NULL ) 
          {
               cout << "List is empty (Free list from top).\n" ;
          }
          else 
          {
               cout << "\nFree list from top - \n" ;
               while( node != NULL) 
               {
                    cout << "     Add time - " << node->genTime << " (count-" << nodeCount << ")\n" ;
                    if( node->next == NULL) {
                         cout << "     This is the last node.\n" ;
                         // this is the only node
                         head = NULL ;
                         tail = NULL ;
                         delete[] node ;
                         node = NULL ;
                    } 
                    else
                    {
                         cout << "     More than one node.\n" ;
                         head = node->next ;
                         head->prev = NULL ;
                         delete[] node ;
                         node = head ; 
                    }
                    nodeCount-- ;
               }
          }
          
          return nodeCount ;
     } ;

     int dumpListFromBottom()
     { 
          listNode *node = tail ;
          if( node == NULL ) 
          {
               cout << "List is empty.\n" ;
          }
          else 
          {
               cout << "\nDump list from bottom - \n" ;
               while( node != NULL) 
               {
                    cout << "     Add time - " << node->genTime << " (count-" << nodeCount << ")\n" ;
                    node = node->prev ;
               }
          }
          
          return nodeCount ;
     } ;
     
     time_t   linkLastTime ;
     
     int      nodeCount ; 

     listNode *head ;
     listNode *tail ;

} ;

//TEST(MathTest, TwoPlusTwoEqualsFour) {
//        EXPECT_EQ(2 + 2, 4);
//}
//
//TEST(coderTest, constructor) {
//     coder c ;
//     EXPECT_EQ(c.x, 0);
//}
//
//TEST(coderTest, constructorNew) {
//     coder *c = new coder ;
//     EXPECT_TRUE( c != NULL );
//}
//
//
//TEST(coderTest, incrFunction) {
//     coder c ;
//     EXPECT_EQ(c.incr(), 1);
//}


TEST(linkedListTests, constructor) {
     linkedList l ;
}

TEST(linkedListTests, dumpFromTop_Empty) {
     linkedList l ;
     l.dumpListFromTop() ;
}

TEST(linkedListTests, freeFromTop_Empty) {
     linkedList l ;
     EXPECT_EQ(l.freeListFromTop(), 0) ;
     EXPECT_EQ(l.nodeCount, 0) ;

}


TEST(linkedListTests, dumpFromBottom_Empty) {
     linkedList l ;
     l.dumpListFromBottom() ;
}

TEST(linkedListTests, addNodeAtEnd_ONE) {
     linkedList l ;
     EXPECT_EQ(l.addNodeAtEnd(time(NULL)), 1) ;
     EXPECT_EQ(l.nodeCount, 1) ;
}

TEST(linkedListTests, freeFromTop_ONE) {
     linkedList l ;
     EXPECT_EQ(l.addNodeAtEnd(time(NULL)), 1) ;

     EXPECT_EQ(l.freeListFromTop(), 0) ;
     EXPECT_EQ(l.nodeCount, 0) ;
}


TEST(linkedListTests, addNodeAtEnd_TWO) {
     linkedList l ;
     l.addNodeAtEnd(time(NULL)) ;
     EXPECT_EQ(l.addNodeAtEnd(time(NULL)), 2) ;
}

TEST(linkedListTests, addNodeAtEnd_THREE) {
     linkedList l ;
     l.addNodeAtEnd(time(NULL)) ;
     l.addNodeAtEnd(time(NULL)) ;
     EXPECT_EQ(l.addNodeAtEnd(time(NULL)), 3) ;
}


int main(int argc, char **argv)
{

     cout << "argc - " << argc << "\n" ;
     cout << "   argv[0] - " << argv[0] << "\n" ;
     if(argc >= 2 )cout << "   argv[1] - " << argv[1] << "\n" ;
  
     if( (argc >= 2) && (0 == strcmp(argv[1], "-test")) )
     {
          int testResults = 0 ;
          ::testing::InitGoogleTest( &argc, argv );

          testResults = RUN_ALL_TESTS() ;
     }

     //coder c ;
     //coder *cp = new coder ;

     //printf( "coder main.\n");
     //printf( "This is a test of the emergency broadcasting system.\n");
     //for (int i = 0; i < 20 ; ++i)
     //{
     //     c.incr() ;
     //}

     //cout << "cp - " ;
     
     linkedList l ;

     for (int i = 0; i < 5 ; ++i)
     {
          l.addNodeAtEnd(time(NULL)) ;
          sleep(1);
     }

     l.dumpListFromTop() ;
     l.freeListFromTop() ;
     l.dumpListFromBottom() ;

     return 0;
     //return ;
}

