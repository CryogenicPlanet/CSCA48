/*
A2 Custom Tester Project
*/
#include <stdbool.h>
#include<string.h>
#include <stdlib.h>
#include"BSTs_1005934198.c"


double findHarmFreq(double curFreq, int semitones){
    for(int i = 0; i < 100; i++){
        if(fabs(note_freq[i] -curFreq) < 1e-15){
            if(i + semitones <= 99 && i + semitones >= 0){
                return note_freq[i+semitones];
            }
        }
    }
    return -1.0;
}

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
bool checkShifted(BST_Node *root, BST_Node *harmonized, int semitones, double time_shift){
    BST_Node *temp = BST_search(root,harmonized->bar,harmonized->index + time_shift);
    double testFreq = findHarmFreq(temp->freq,semitones);
    if(temp != NULL){
        if(fabs(temp->freq - testFreq) < 1e-15){
            return true;
        }
    }
    return false;
}

bool harmonizeCheck(BST_Node *root, BST_Node *harmonized, int semitones, double time_shift){
    if(harmonized == NULL){return false;}
    if(harmonized->left != NULL){
        if(harmonizeCheck(root,harmonized->left,semitones,time_shift) == false){
            return false;
        }
    }
    if(harmonized != NULL){
        if((BST_search(root,harmonized->bar,harmonized->index)== NULL) && (checkShifted(root,harmonized,semitones,time_shift) ==false) && (checkShifted(root,harmonized,semitones,time_shift +  1e-05) == false)){
            return false;
        }
    }
    if(harmonized->right != NULL){
         if(harmonizeCheck(root,harmonized->right,semitones,time_shift) == false){
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
    read_note_table();
   
    printf("Use this test file under the assumption that you passed all test cases in A2_test_driver.c\n");
    printf("To change song pass the song file name as Argument 1\n");
    int printINOrder = 0;
    printf("Do you want to print tree traversals?\n");
    printf("0. Yes (default)\t");
    printf("1. No \n");
    scanf("%d",&printINOrder);
    system("clear");
    char *inputSong = "./stairway.txt";
    
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
    if(printINOrder == 0){BST_inOrder(root,0);}
    printf("Passed Test 2? - check message above to see if all notes were inserted\n");


   

    // Test 3
    // Shift Frequency

    printf("--- Test 3 Shift Frequency --- \n");

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
    printf("--- Test 4 --- \n");
    int semitones;
    double timestep;
    printf("Choose semitones \n");
    scanf("%d",&semitones);
    printf("Choose timestep\n");
    scanf("%lf",&timestep);
    int originalSize = BST_size(root);
    BST_Node *harmonized;
    harmonized = BST_harmonize(root,semitones,timestep);
    printf("--- Below is InOrder Traversal of Harmonized Output --- \n");
    if(printINOrder == 0){BST_inOrder(harmonized,0);}
    
    int harmoinzedSize = BST_size(harmonized);
    printf("--- Check that is has ~2x Elements as original\n Original %d, Harmonized %d ---\n",originalSize,harmoinzedSize);
    if(harmonizeCheck(root,harmonized,5.0,0.2) == false){
        printf("Failed Test 4 to harmonize all values correctly\n");
        printf("Pls check the +- added to duplicate indexs, the code checks for + 1e-05 if you have a different value either change this file or your code\n");
        return 1;
    }


    printf("Passed Test 4? Harmonize Basic, not a rigours check for Harmonize\n");


    // Test 5 
    // Double Harmonize
    printf("--- Test 5 -- \n");
    BST_Node *doubleHarmonize; 
    printf("Choose semitones \n");
    scanf("%d",&semitones);
    printf("Choose timestep\n");
    scanf("%lf",&timestep);  
    doubleHarmonize = BST_harmonize(harmonized,semitones,timestep);
    printf("--- Below is InOrder Traversal of Harmonized Output --- \n");
    if(printINOrder == 0){BST_inOrder(doubleHarmonize,0);}
    int doubleHarmonizedSize = BST_size(doubleHarmonize);
    printf("--- Check that is has  Elements as original\n Original %d, Harmonized %d, Double Harmonized %d ---\n",originalSize,harmoinzedSize,doubleHarmonizedSize);
    if(harmonizeCheck(root,harmonized,5.0,0.2) == false){
        printf("Failed Test 4 to harmonize all values correctly\n");
        printf("Pls check the +- added to duplicate indexs, the code checks for + 1e-05 if you have a different value either change this file or your code\n");
        return 1;
    }
    printf("Passed Test 5? Double Harmonize, not a rigous check for Harmonize\n");


    // Make Playlist Test
    BST_makePlayList(doubleHarmonize);
    play_notes(2);


    return 0;
}

