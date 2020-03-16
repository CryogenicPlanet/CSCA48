/*
A2 Custom Tester Project
*/
#include <stdbool.h>
#include<string.h>
#include"BSTs.c"


BST_Node * read_song(char * songName)
{
    // Read note names and frequencies from file
    FILE *f;
    char line[1024];
    int idx;
    int bar;
    double index;
    double freq_src;
    //char * freq_input = NULL; 
    char freq_name[5];
    BST_Node *newSong = NULL;
    BST_Node *newNote = NULL;
   
    f=fopen(songName,"r");
    if (f==NULL)
    {
      printf("Unable to open song file!\n");
      return NULL;
    }
    
    idx=0;
    while (fgets(&line[0],1024,f))
    {
        //printf("Reading file at line %d\n",idx);
        sscanf(line,"%d\t%lf\t%s",&bar,&index,freq_name);
        //printf("Read Elements %s\n",freq_name);
        
        //printf("-\n");

        //freq_src = -1.0;
        //printf("Outside for loop\n");   
        for(int i = 0; i < 100;i++){
            if(strcmp(freq_name,note_names[i]) == 0){
                freq_src = note_freq[i];
                //printf("Found Frequency \n");
            }
        }
        if(freq_src == -1.0){
            return NULL;
        }
        //printf("Before creating new node\n");
        newNote = newBST_Node(freq_src,bar,index);
        if(newNote == NULL){
            return NULL;
        }
        newSong = BST_insert(newSong,newNote);
        idx++;
    }
    printf("Added %d notes to create a new song !\n",idx);
    return newSong;
}

bool inOrderShiftCheck(BST_Node *root,double freq_src){
    if(root == NULL){return false;}
    if(root->left != NULL){
        if(inOrderShiftCheck(root->left,freq_src) == false){
            return false;
        }
    }
    if(root != NULL){
        if(fabs(root->freq - freq_src) <1e-15){
            return false;
        }
    }
    if(root->right != NULL){
        if(inOrderShiftCheck(root->right,freq_src) == false){
            return false;
        }
    }
    return true;
}

int BST_size(BST_Node *node) {
    if(node == NULL) return 0;
    
    else {
        return BST_size(node -> left) + BST_size(node -> right) + 1;
    }
}

int main(int argc, char const *argv[])
{
    printf("Use this test file under the assumption that you passed all test cases in A2_test_driver.c\n");
    printf("To change song pass the song file name as Argument 1\n");

    read_note_table();
    
    char *inputSong = "./scherzino.txt";
    
    if(argv[1] != NULL){
        strcpy(inputSong,argv[1]);
    }
    
    
    BST_Node *root = NULL;

    // Test 1
    // Trivial Print Test
    // printing NUll list
    BST_inOrder(root,0);
    BST_preOrder(root,0);
    BST_postOrder(root,0);
    printf("Passed 1 Travesing Null List\n");


    printf("---Test 2 ---\n");
    // Test 2
    // Insert a full song
    root = read_song(inputSong);
    if(root == NULL){
        printf("Failed to insert notes from %s song into binary tree \n",inputSong);
        return 1;
    }
    BST_inOrder(root,0);
    printf("Passed Test 2? - check message above to see if all notes were inserted\n");


    printf("--- Test 3 Shift Frequency --- \n");

    // Test 3
    // Shift Frequency


    char freq_src[5],freq_dst[5];
    printf("Choose frequency to change only 5 Characters\n");
    scanf("%s",freq_src);
    printf("Choose destination frequency\n");
    scanf("%s",freq_dst);
    BST_shiftFreq(root,freq_src,freq_dst);
    double freq;
    freq = -1.0; 
    for(int i = 0; i < 100;i++){
        if(strcmp(freq_src,note_names[i]) == 0){
            freq = note_freq[i];
        }
    }
    if(inOrderShiftCheck(root,freq) == false){
        printf("Failed Test 3, did not change all the frequencies\n");
        return 1;
    }
    printf("Passed Test 3 Shifted Frequencies\n");

    // Test 4
    // Harmonize
    int preCount;
    int postCount;
    preCount = BST_size(root);
    printf("preCount %d",preCount);
    BST_Node *harmonized;
    harmonized = BST_harmonize(root,4,0.1);
    postCount = BST_size(harmonized);
    if(preCount == postCount){
        printf("Failed Test 4, did not change all frequencies\n");
        return 1;
    }
    printf("Passed Test 4 Harmonize Basic\n");


    return 0;
}

