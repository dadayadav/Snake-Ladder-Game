#include<bits/stdc++.h>
#include<unordered_map>
#include<vector>
#include<string>
#include <unistd.h>
#define defaultPlayer 2
#define playBoardSize 100
using namespace std;

int rollDice(){
    int output = rand()%6;
    if(output == 0) return 6;
    return output;
}

unordered_map<int, string> playerName;
unordered_map<int,int>playerPosition;
unordered_map<int,int>snakeLadderInfo;
queue<int> playerNumberQueue;
void init(int = defaultPlayer);

int setSnakePosition(){
    /* 8 snakes */

    snakeLadderInfo[27] = 5;
    snakeLadderInfo[40] = 3;
    snakeLadderInfo[43] = 18;
    snakeLadderInfo[54] = 31;
    snakeLadderInfo[66] = 45;
    snakeLadderInfo[76] = 58;
    snakeLadderInfo[89] = 53;
    snakeLadderInfo[99] = 41;
    return snakeLadderInfo.size();
}

int setLadderPosition(){
    /* 8 ladders */

    snakeLadderInfo[4] = 25;
    snakeLadderInfo[13] = 46;
    snakeLadderInfo[33] = 49;
    snakeLadderInfo[50] = 69;
    snakeLadderInfo[42] = 63;
    snakeLadderInfo[62] = 81;
    snakeLadderInfo[74] = 92;
    snakeLadderInfo[75] = 95;
    return snakeLadderInfo.size();
}



void init(int totalPlayer){
    playerName.clear();
    playerPosition.clear();
    snakeLadderInfo.clear();
    cout<<"Hello Guys.........."<<endl;
    /*cout<<"Please Enter the Number of players..."<<endl;
    cin>>totalPlayer;
    cout<<totalPlayer<<endl;*/
    cout<<"*****************"<<endl;
    cout<<"Please Enter the Name of players..."<<endl;
    for(int i = 0; i < totalPlayer;i++)
    {
        string name;
        getline(cin,name);
        playerName[i+1] = name;
        playerNumberQueue.push(i+1);
    }
    cout<<endl;
    for(auto i: playerName){
        cout<<"Welcome "<< i.second<<" your number is: "<<i.first<<endl;
        playerPosition[i.first] = 0;
    }
    cout<<endl;
    cout<<"*****************"<<endl;
    cout<<"Well Done................."<<endl;

    cout<<"INFO about the ladders and snakes positions are................."<<endl;
    int totalSnake = setSnakePosition();
    int totalLadder = setLadderPosition()-totalSnake;
    cout<<endl;
    cout<<"Total Snakes are "<<totalSnake<<" **********"<<endl;
    int counts = 0;
    for(auto i: snakeLadderInfo)
        {
            counts++;
            cout<<i.second<<"--------------------->"<<i.first<<endl;
            if(counts == totalSnake) break;
        }
    cout<<endl;
    cout<<"Total ladder are "<<totalLadder<<" **********"<<endl;
    counts = 0;
    cout<<endl;
    for(auto i: snakeLadderInfo)
        {
            counts++;
            cout<<i.first<<"=====================>"<<i.second<<endl;
            if(counts == totalLadder) break;
        }


    cout<<endl;
    cout<<"******************************************************"<<endl;
    cout<<"Let's start the game.........."<<endl;
    cout<<endl;
    cout<<"sequence of playing game is...... "<<endl;

    for(int i=0;i<totalPlayer;i++){
        int c = playerNumberQueue.front();
        playerNumberQueue.pop();
        if(i != totalPlayer-1)
            cout<<c<<", ";
        else
            cout<<c<<endl;
        playerNumberQueue.push(c);
    }

}


int main()
{
    init();
    vector<string> winners;
    int iteration = 0;
    srand(time(0));
    while(!playerNumberQueue.empty() && iteration<1000){

        // cout<<"Total player in queue: "<< playerNumberQueue.size()<<endl;
        // cout<<"Total player wins: "<<winners.size()<<endl;

        int currPlayer = playerNumberQueue.front();
        playerNumberQueue.pop();
        string dicerol;
        cout<<"Press enter to roll the dice................ ";
        getline(cin, dicerol);
        int diceOutput = rollDice();
        cout<<endl;
        sleep(2);
        cout<<"Dice output: "<<diceOutput<<endl;

        // getline(cin, dicerol);
        
        int afterDicePosition = playerPosition[currPlayer] + diceOutput;
        int currPosition = playerPosition[currPlayer];
        int tempCurrPosition = afterDicePosition;
        /*check for snake or ladder at new position*/
        if(snakeLadderInfo.find(afterDicePosition) != snakeLadderInfo.end()){
            tempCurrPosition = snakeLadderInfo[afterDicePosition];
            if(tempCurrPosition>afterDicePosition) cout<<"Congrats.. you got a ladder===================================="<<endl;
            else cout<<"Oops, Snakes bite you..................................................."<<endl;
        }

        if(tempCurrPosition>playBoardSize)
            {
                cout<<"You need "<<(playBoardSize-currPosition)<<" to win the game"<<endl; 
            }
            else
                currPosition = tempCurrPosition;
        sleep(2);

        if(currPosition >= playBoardSize){
            cout<<"*-*-*-*-*-*-**--*-*-*-*-*-*-* Wooooooooooooo ";
            cout<<" Player number: "<< currPlayer << " ---> " << playerName[currPlayer] << " wins...." << endl;
            playerPosition[currPlayer] = playBoardSize;
            winners.push_back(playerName[currPlayer]);
            cout<<playerName[currPlayer]<<" position is = "<< playBoardSize<<endl;
            cout<<"Wins after iteration..... "<<iteration<<endl;
            cout<<endl;
        }
        else{
            playerPosition[currPlayer] = currPosition;
            playerNumberQueue.push(currPlayer);
            cout<<playerName[currPlayer]<<" position is = "<< currPosition<<endl;
            cout<<endl;
        }
        iteration++;
    }
}

