#include <bits/stdc++.h>
#include<iostream>
#include <tuple>
#include <queue>
#include <unordered_map>
using namespace std;
typedef tuple<int, int, int> tupl;      //Declaring tuple FOR flights

vector<vector<int> > adjMatrix;         // DFS memoization

typedef struct ticket{
       int id;
       string name;
       int noofpeople;
       int tc;
       string startlocn;
       string destinylocn;
       string via;
       int age;
       struct ticket *next;
   }ticket;
class travel{
   ticket *book[10];
   public:
   string codes[5]={"MUMBAI", "NASHIK" , "PUNE" , "AURANGABAD" , "AHMEDNAGAR"};
   int i=0,j;


void bookticket(int price,int i,int s,int d, string v){
     ticket *node;
     node = new ticket;
     node->id=i;
     cout<<"------------Enter name-----------> ";
     cin>>node->name;
     cout<<"------------Enter age------------> ";
     cin>>node->age;
     cout<<"------------Enter no. of people--> ";
     cin>>node->noofpeople;
     int totalcost  = node->noofpeople * price;
     node->tc=totalcost;
     node->startlocn=codes[s];
     node->destinylocn=codes[d];
     node->via=v;
     book[i]=node;
     book[i]->next=NULL;
     cout<<"\n____________Ticket has been booked !!_________________\n";
}

void comparetickets()
{
    int j=0;
    while(book[j]->id<10&&book[j]->id>=0&&book[j]->age<100)
    {
        cout<<"\n|-------Ticket no. "<<book[j]->id + 1<<"----------------------------|\n";
        cout<<"|---Travel type                  :"<<book[j]->via<<"\n";
        cout<<"|---Route                        :"<<book[j]->startlocn<<" to "<<book[j]->destinylocn<<"\n";
        cout<<"|---Senior Passenger Name        :"<<book[j]->name<<"\n";
        cout<<"|---Senior Passenger Age         :"<<book[j]->age<<"\n";
        cout<<"|---Total no of people traveling :"<<book[j]->noofpeople<<"\n";
        cout<<"|---Total cost of traveling      :"<<book[j]->tc<<"\n";
        cout<<"________________________________________________\n";
        j++;
    }
}

//ALL FLIGHT DATA WITH DIJKSTRAS
long findCheapestFLIGHT(int cities, vector<vector<int>> &flights, int src, int dst, int stops)
{
    vector<vector<pair<int, int>>> adjList(cities);   //Adjacency Matrix


    for (auto flight : flights)                       //Traverse flight[][]
    {
        // Create Adjacency Matrix
        adjList[flight[0]].push_back({flight[1], flight[2]});
    }

    priority_queue<tupl,vector<tupl>,greater<tupl>>pq;               //Implementing Priority Queue



    tupl t = make_tuple(0, src, stops);
    pq.push(t);


    while (!pq.empty())                              // While PQ is not empty
    {
        tupl t = pq.top();
        pq.pop();

        if (src == dst)
            return 0;

        int cost = get<0>(t);                       //it accepts the index and tuple name as arguments to access a particular tuple element.
        int current = get<1>(t);
        int stop = get<2>(t);

        if (current == dst)
            return cost;                            // Return the Answer

        if (stop >= 0)
        {
            for (auto next : adjList[current])
            {

                tupl t = make_tuple((cost + next.second), next.first,stop - 1);
                pq.push(t);
            }
        }
    }

    return -1;
}
// ALL BUS DATA WITH DFS...


int DFS(int node, int stops, int dst, int cities)          // Function to implement DFS Traversal
{
    if (node == dst)
        return 0;

    if (stops < 0)
    {
        return INT_MAX;
    }

    int cost = INT_MAX;

    for (int neighbour = 0; neighbour < cities; ++neighbour)      // Traverse adjacency matrix of source node
    {
        int weight = adjMatrix[node][neighbour];
        if (weight > 0)
        {
            int minVal = DFS(neighbour, stops - 1, dst, cities);        // Recursive DFS call for child node
            if (minVal + weight > 0)
                cost = min(cost, minVal + weight);
        }
    }


    // Return cost
    return cost;
}

int findCheapestBUS(int cities,vector<vector<int> >& buscost,int src, int dst, int stops)// Function to find the cheapest price
{
    adjMatrix.resize(cities + 1,vector<int>(cities + 1, 0));     // Resize Adjacency Marix

    for (auto cost : buscost)                                   // Traverse bus[][]
    {
        adjMatrix[cost[0]][cost[1]] = cost[2];                  // Create Adjacency Matrix
    }

    int cost = DFS(src, stops , dst, cities);
    return cost >= INT_MAX ? -1 : (int)cost;                    // Return the cost
}

// ALL TRAIN DATA WITH BFS..

int findCheapestTRAIN(int cities, vector<vector<int> >& traincost, int src, int dst, int stops) // Function to implement BFS
{
    unordered_map<int, vector<pair<int, int> > > adjList;

    for (auto train : traincost)                         // Traverse flight[][]
    {
        adjList[train[0]].push_back({ train[1], train[2] });        // Create Adjacency Matrix
    }

    queue<pair<int, int> > q;                       // < city, distance from source > pair
    q.push({ src, 0 });

    int srcDist = INT_MAX;                         // Store the Result

    while (!q.empty() && stops-- >= 0)             // Traversing the Matrix
    {
        int qSize = q.size();

        for (int i = 0; i < qSize; i++)
        {
            pair<int, int> curr = q.front();
            q.pop();

            for (auto next : adjList[curr.first])
            {
                if (srcDist < curr.second + next.second)    // If source distance is already least the skip this iteration
                   continue;

                q.push({ next.first, curr.second + next.second });

                if (dst == next.first)
                {
                    srcDist = min( srcDist, curr.second + next.second);
                }
            }
        }
    }
    return srcDist == INT_MAX ? -1 : srcDist;               // Returning the Answer
}



void FLIGHTScost(){
    int destCity,sourceCity, stops = 0;
    int totalCities = 5;
    string f = "FLIGHT";
    vector<vector<int>> flights = {{0,1,1500},{1,0,1700},{0,2,2000},{2,0,1850},{0,3,1900},{3,0,1800},{1,2,700},{2,1,800},{1,3,1100},{3,1,1250},{2,3,2500},{3,2,2700}};
    cout<<"Enter the Start Location"<<endl;
    cin>>sourceCity;
    cout<<"Enter the Destination Location"<<endl;
    cin>>destCity;

    long cost = findCheapestFLIGHT(totalCities, flights,sourceCity, destCity, stops);
    if(cost == -1){
        cout<<"\n\nNO direct flight available!!!\n";
    }
    else{
    cout <<"The Cheapest flight cost to travel from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is : Rs."<<cost<<"/-\n";
    }
    int t=0;;
    cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
    cin>>t;
    if(t==1)
    {
        bookticket(cost,i,sourceCity,destCity,f);
        i++;
    }
}

void FLIGHTSdistance(){
        int destCity2,sourceCity2;
        int totalCities = 5,stops=0;
         string f = "FLIGHT";
        // Input flight : {Source,
        // Destination, Cost}
        vector<vector<int>> flightdis = {{0,1,212},{1,0,212},{0,2,360},{2,0,360},{0,3,195},{3,0,195},{1,2,80},{2,1,80},{1,3,110},{3,1,110},{2,3,200},{3,2,200}};

        cout<<"Enter the Start Location"<<endl;
        cin>>sourceCity2;
        cout<<"Enter the Destination Location"<<endl;
        cin>>destCity2;

        long dist = findCheapestFLIGHT(totalCities, flightdis,sourceCity2, destCity2, stops);
        if(dist == -1){
            cout<<"\n\nNO direct flight available!!!\n";
        }
        else{
        cout <<"\nThe shortest route from "<<codes[sourceCity2]<<" to "<<codes[destCity2]<<" is "<<dist<<" Kms.";
        }
        int t=0;
        int cost = dist*5;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity2,destCity2,f);
            i++;
        }


}

void FLIGHTStime(){
        int destCity3,sourceCity3;
        int totalCities = 5,stops=0;
        string f = "FLIGHT";
        vector<vector<int>> flighttime = {{0,1,65},{1,0,72},{0,2,90},{2,0,75},{0,3,67},{3,0,91},{1,2,34},{2,1,40},{1,3,32},{3,1,36},{2,3,45},{3,2,43}};

        cout<<"Enter the Start Location"<<endl;
        cin>>sourceCity3;
        cout<<"Enter the Destination Location"<<endl;
        cin>>destCity3;

        long time = findCheapestFLIGHT(totalCities, flighttime, sourceCity3, destCity3,stops);
        if(time == -1){
            cout<<"\n\nNO direct flight available!!!\n";
        }
        else{
        cout << "\n"<<"The minimum time required to travel from "<<codes[sourceCity3]<<" to "<<codes[destCity3]<<" is "<< time << " min.";
        }
        int t=0;
        long cost = time*42;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity3,destCity3,f);
            i++;
        }
}




void BUScost(){

    int stops=1,sourceCity,destCity;
    int totalCities = 5;
    string f = "BUS";

    vector<vector<int> > buscost = { {0,1,225},{1,0,225},{0,2,350},{2,0,350},{0,3,270},{3,0,270},{0,4,370},{4,0,370},{1,2,70},{2,1,70},
                        {1,3,95},{3,1,95},{1,4,275},{4,1,275},{2,3,160},{3,2,160},{2,4,210},{4,2,210},{3,4,110},{4,3,110} };// Input bus : {Source,Destination, Cost}

        cout<<"Enter the Start Location "<<endl;
        cin>>sourceCity;
        cout<<"Enter the Destination Location "<<endl;
        cin>>destCity;

        int cost = findCheapestBUS( totalCities, buscost, sourceCity, destCity, stops);          // Function Call
        cout <<"The Cheapest bus cost to travel from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is :"<<cost;
        int t=0;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity,destCity,f);
            i++;
        }

}

void BUSdistance(){
    int sourceCity,destCity;
    int totalCities = 5,stops=1;
    string f = "BUS";
    vector<vector<int> > busdist = { {0,1,212},{1,0,212},{0,2,360},{2,0,360},{0,3,195},{3,0,195},{0,4,457},{4,0,457},{1,2,80},{2,1,80},
                        {1,3,110},{3,1,110},{1,4,300},{4,1,300},{2,3,200},{3,2,200},{2,4,200},{4,2,200},{3,4,97},{4,3,97} };// Input bus : {Source,Destination,distance}

    cout<<"Enter the Start Location"<<endl;
    cin>>sourceCity;
    cout<<"Enter the Destination Location"<<endl;
    cin>>destCity;

        int dist = findCheapestBUS(totalCities, busdist, sourceCity, destCity,stops);                       // Function Call
        cout <<"\nThe shortest route by bus from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is "<<dist<<" Kms.";
        int t=0;
        int cost = dist * 0.8;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity,destCity,f);
            i++;
        }
}

void BUStime(){
    int sourceCity,destCity;
    int totalCities = 5,stops = 1;
    string f = "BUS";
    vector<vector<int> > bustime = { {0,1,267},{1,0,267},{0,2,350},{2,0,350},{0,3,240},{3,0,240},{0,4,329},{4,0,329},{1,2,100},{2,1,100},
                        {1,3,125},{3,1,125},{1,4,325},{4,1,325},{2,3,230},{3,2,230},{2,4,245},{4,2,245},{3,4,117},{4,3,117} }; // Input bus : {Source,Destination,time}

    cout<<"Enter the Start Location"<<endl;
    cin>>sourceCity;
    cout<<"Enter the Destination Location"<<endl;
    cin>>destCity;

    int time = findCheapestBUS( totalCities, bustime, sourceCity, destCity,stops);                     // Function Call
    cout << "\n"<<"The minimum time required to travel from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is "<< time << " min.";
    int t=0;
    int cost = time * 0.8;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity,destCity,f);
            i++;
        }

}




void TRAINcost()
{
    int stops=0,destCity,sourceCity;
    int totalCities = 5;
    string f= "TRAIN";
    vector<vector<int> > trains = { {0,1,150},{1,0,130},{0,2,220},{2,0,245},{0,3,120},{3,0,145},{0,4,350},{1,2,320},{2,1,40},
                        {1,3,45},{3,1,30},{2,3,80},{3,2,60},{2,4,95},{4,2,115} };
    cout<<"Enter the Start Location"<<endl;
    cin>>sourceCity;
    cout<<"Enter the Destination Location"<<endl;
    cin>>destCity;

    long cost = findCheapestTRAIN( totalCities, trains, sourceCity, destCity, stops);    // Function Call
    if(cost == -1){
        cout<<"\n\nNO Trains available!!!\n\n";
    }
    else{
    cout <<"The Cheapest train cost to travel from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is :"<<cost;
    }
        int t=0;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity,destCity,f);
            i++;
        }

}

void TRAINdistance()
{
    int sourceCity,destCity;
    int totalCities = 5,stops=0;
    string f= "TRAIN";
    vector<vector<int> > traindist = { {0,1,212},{1,0,212},{0,2,360},{2,0,360},{0,3,195},{3,0,195},{0,4,457},{1,2,80},{2,1,80},
                        {1,3,110},{3,1,110},{2,3,200},{3,2,200},{2,4,200},{4,2,200} };

    cout<<"Enter the Start Location"<<endl;
    cin>>sourceCity;
    cout<<"Enter the Destination Location"<<endl;
    cin>>destCity;

    int dist = findCheapestTRAIN(totalCities,traindist,sourceCity,destCity,stops);     // Function Call
    if(dist == -1){
        cout<<"\n\nNO Trains available!!!\n\n";
    }
    else{
     cout <<"\nThe shortest route by train from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is "<<dist<<" Kms.";
    }
      int t=0;
      int cost=dist*0.4;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;
        if(t==1)
        {
            bookticket(cost,i,sourceCity,destCity,f);
            i++;
        }
}

void TRAINtime()
{
    int sourceCity,destCity;
    int totalCities = 5,stops=0;
    string f= "TRAIN";
    vector<vector<int> > traintime = { {0,1,217},{1,0,205},{0,2,253},{2,0,285},{0,3,227},{3,0,245},{0,4,279},{1,2,89},{2,1,110},
                        {1,3,85},{3,1,106},{2,3,150},{3,2,143},{2,4,190},{4,2,175} };

    cout<<"Enter the Start Location"<<endl;
    cin>>sourceCity;
    cout<<"Enter the Destination Location"<<endl;
    cin>>destCity;

    int time = findCheapestTRAIN(totalCities,traintime,sourceCity,destCity,stops);
    if(time == -1){
        cout<<"\n\nNO Trains available!!!\n\n";
    }
    else{
     cout << "\n"<<"The minimum time required to travel from "<<codes[sourceCity]<<" to "<<codes[destCity]<<" is "<< time << " min.";
    }
        int t=0;
        int cost= 0.4*time;
        cout<<"\n    Wanna book ticket ?(YES - 1 / NO -0)  ";
        cin>>t;

        if(t==1)
        {
            bookticket(cost,i,sourceCity,destCity,f);
            i++;
        }

}

};

int main()
{
    cout<<"\n\n";
    cout<<"\t\t\t*     *  ******  *        *****    ****   **   **  ******\n";
    cout<<"\t\t\t*     *  *       *        *       *    *  * * * *  *\n";
    cout<<"\t\t\t*  *  *  ****    *        *       *    *  *  *  *  ****\n";
    cout<<"\t\t\t* * * *  *       *        *       *    *  *     *  *\n";
    cout<<"\t\t\t**   **  ******  *******  *****    ****   *     *  ******\n\n";

    int ch,chi,choice,ch1;
    travel t;
    cout<<"Given below are the codes that represents the particular city. \n"<<endl;
    cout<<"       0-Mumbai \n       1-Nashik \n       2-Pune \n       3-Delhi \n       4-Kolkata  \n"<<endl;
    do{
    cout<<"----------------------------------------------------------------------------";
    cout<< "\nEnter your mode of travelling:\n  \n1)flight    2)bus     3)train     4)Compare booked tickets\n"<<endl;
    cout<<"----------------------------------------------------------------------------\n";
    cin >> ch;
    switch(ch){

        case 1:
            do{
                cout<<"Enter the method to sort your travel: \n";
                cout<<"---------------------------------------";
                cout<< "\n1) cost     2)distance      3)time\n"<<endl;
                cout<<"---------------------------------------";
                cout<<"Enter your choice: "<<endl;
                cin >> chi;
                cout<<"\n\n";
                switch (chi)
                {
                case 1:
                    t.FLIGHTScost();
                    break;
                case 2:
                    t.FLIGHTSdistance();
                    break;
                case 3:
                    t.FLIGHTStime();
                    break;
                }
                cout<<"\n\nEnter 1, if you want to view more details.\n";

                cin>>ch1;
            }while(ch1==1);
            break;
        case 2:
            do{
                cout<<"Enter the method to sort your travel: \n";
                cout<<"---------------------------------------";
                cout<< "\n1) cost     2)distance      3)time\n"<<endl;
                cout<<"---------------------------------------";
                cout<<"Enter your choice: "<<endl;
                cin >> chi;
                switch (chi)
                {
                case 1:
                    t.BUScost();
                    break;
                case 2:
                    t.BUSdistance();
                    break;
                case 3:
                    t.BUStime();
                    break;
                }
                cout<<"\n\nEnter 1, if you want to view more details for buses\n";
                cin>>ch1;
            }while(ch1==1);
            break;
        case 3:
            do{
                cout<<"Enter the method to sort your travel: \n";
                cout<<"---------------------------------------";
                cout<< "\n1) cost     2)distance      3)time\n"<<endl;
                cout<<"---------------------------------------";
                cout<<"Enter your choice: "<<endl;
                cin >> chi;
                switch (chi)
                {
                case 1:
                    t.TRAINcost();
                    break;
                case 2:
                    t.TRAINdistance();
                    break;
                case 3:
                    t.TRAINtime();
                    break;
                }
                cout<<"\n\nEnter 1, if you want to view more details for Trains\n";
                cin>>ch1;
            }while(ch1==1);
            break;
        case 4:
            t.comparetickets();
            break;

    }
    cout<<"Press 1 to continue:\n";
    cin>>choice;
    }while(choice==1);
    return 0;
}
