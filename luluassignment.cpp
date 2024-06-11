#include<iostream>
#include<ctype.h>
#include<iomanip>

using namespace std;
int PLAN = 0;
int CUSTOMER  = 0;
int POSITION = 0;

class TrainingPlan{
    string tpName;
    int sessionPerWeek;
    float feesPerWeek;
    public:
        TrainingPlan(){
            tpName = "";
            sessionPerWeek = 0;
            feesPerWeek = 0;
        }
        TrainingPlan(string n, int s, float FPW){
            tpName = n;
            sessionPerWeek = s;
            feesPerWeek = FPW;
            PLAN++;
        }
        
        void setPlan(TrainingPlan plans[]){
            cout<<"Register For Plan Name : ";
            cin.get();
            getline(cin, tpName);
            cout<<"Register For Sesion Per Week : ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"Register For Fees Per Week : ";
            cin>>feesPerWeek;
            cout<<"Successfully created a training plan ! ("<<tpName<<")!\n";
            cin.get();
            PLAN++;
        }
        void updatePlan(){
            cout<<"Plan Name("<<tpName<<") : \n";
            cout<<"Register For Sessions Ser Week ("<<sessionPerWeek<<") : ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"Register For Fees Per Week ("<<feesPerWeek<<") : ";
            cin>>feesPerWeek;
            cout<<"Successfully updated the training plan ! ("<<tpName<<")!\n";
            cin.get();
        } 
        string getPlanName() {return tpName;}
        float getFeesPerWeek() {return feesPerWeek;}
        int getSessionsPerWeek() {return sessionPerWeek;}
        void displayPlan(){
            cout<<setw(20)<<tpName
                <<setw(20)<<sessionPerWeek
                <<setw(15)<<feesPerWeek;
        }
};

class Customer{
    string cName;
    TrainingPlan trainingPlan;
    float currentWeight;
    int privateHours[4];
    bool privateHourOnOff[4];
    int learntPosesCount;
    string LearntPoses[10];
    float cost;
    public:
        Customer(){
            cName = "";
            currentWeight = 0;
            cost = 0;
            learntPosesCount = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = 0;
                privateHourOnOff[i] = 0;
            }
        }
        Customer(string n, TrainingPlan tp, float w, int h[4], bool OnOff[4]){
            cName = n;
            trainingPlan = tp;
            currentWeight = w;
            cost = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = h[i];
                privateHourOnOff[i] = OnOff[i];
            }
            CUSTOMER++;
        }
        string setCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Register For The Customer Name : ";
            cin.get();
            getline(cin, cName);

            trainingPlanLabel:
            cout<<"Register For Training Plan - Available Plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Current weight : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                privateHourLabel:
                cout<<"Register For"<<i+1<<" th/st Week Private Hours : \n";
                cin>>privateHours[i];
                if(privateHours[i] < 0 || privateHours[i] > 5) {
                    cout<<"It exceeded 5 or less than 0\n";
                    goto privateHourLabel;
                }

                cout<<"Online/Offline (0/1) : ";
                cin>>o;
                if(o=='0') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            learntPosesCount = 0;
            CUSTOMER++;
            return trainingPlan.getPlanName();
        }
        string updateCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Customer name("<<cName<<") : \n";

            trainingPlanLabel:
            cout<<"Register For Training Plan - Available Plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Current Weight(kg) : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                cout<<"Register For"<<i+1<<" th/st Week Private Hours : \n";
                cin>>privateHours[i];
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='0') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            learntPosesCount = 0;
            return trainingPlan.getPlanName();
        }
        void addLearntPoses(string poses[]){
            char learnt = 'y';
            int ind = 0;
            int learntInd = 0;
            cout<<"Already learnt poses? (y/n) : ";
            cin>>learnt;
            if(learnt=='y') {
                for(int i=0; i<10; i++){
                    cout<<"("<<i+1<<")"<<poses[i];
                    if(i+1 != 10) cout<<" , ";
                }
                while(true){
                    char more = 'y';
                    cout<<"\nEnter pose index : ";
                    cin>>ind;
                    cout<<"Got more?(y/n) : ";
                    cin>>more;
                    learntPosesCount++;
                    LearntPoses[learntInd] = poses[ind-1];
                    learntInd++;
                    if(more!='y') break;
                }
            }
            cout<<endl;
        }
        float getFinalCost(){
            cost = 0;
            cost += trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) cost += 15000*privateHours[i];
                else cost += 17000*privateHours[i];
            }
            return cost - (cost*learntPosesCount)/100;
        }
        float getCost() {
            cost = 0;
            cost += trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) cost += 15000*privateHours[i];
                else cost += 17000*privateHours[i];
            }
            return cost;
        }
        void displayCustomer(){
            cout<<setw(20)<<cName
                <<setw(20)<<trainingPlan.getPlanName()
                <<setw(10)<<learntPosesCount
                <<setw(20)<<getFinalCost();
        }
        void displayCustomerDetails(){
            int online = 0, offline = 0;
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) online++;
                else offline++;
            }
            cout<<setw(30)<<"Custome's Name : "<<setw(20)<<cName<<endl
                <<setw(30)<<"Weight : "<<setw(20)<<currentWeight<<endl
                <<setw(30)<<"Training plan : "<<setw(20)<<trainingPlan.getPlanName()<<endl
                <<setw(30)<<"Learnt poses counts : "<<setw(20)<<learntPosesCount<<endl<<setw(30)<<"Learnt poses : ";
            for(int i=0; i<learntPosesCount; i++) cout<<LearntPoses[i]<<" ,";
            cout<<endl<<setw(30)<<"Sessions per week : "<<setw(20)<<trainingPlan.getSessionsPerWeek()
                <<setw(20)<<trainingPlan.getFeesPerWeek()*4<<endl
                <<setw(30)<<"Private (Online-15000) : "<<setw(20)<<online<<setw(20)<<15000*online<<endl
                <<setw(30)<<"Private (Offline-17000) : "<<setw(20)<<offline<<setw(20)<<17000*offline<<endl
                <<setw(30)<<"DISCOUNT (%) : "<<setw(20)<<learntPosesCount<<setw(20)<<getCost()*learntPosesCount/100<<endl
                <<setw(30)<<"Total Cost : "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
        }
};
class Position{
    string name;
    int poseCount;
    public:
    public:
        string poseType[10];
        string poseName[10];
        Position(){
            name = "";
            poseCount = 0;
        }
        Position(string name, string type[10], string names[10], int pc){
            this->name = name;
            poseCount = pc;
            for(int i=0; i<10; i++){
                poseType[i] = type[i];
                poseName[i] = names[i];
            }
            POSITION++;
        }
        void addPosition(){
            cout<<"Position name : "<<name<<endl;
            cout<<"Positions : \n";
            for(int i=0; i<poseCount; i++) {
                cout<<poseName[i];
                if(i+1 != poseCount) cout<<" , ";
                else cout<<endl;
            }
            if(poseCount == 10) {
                cout<<"10 poses already added\n";
                cin.get();
                return;
            }
            char more = 'y';
            while(true){
                if(poseCount==10) break;

                cout<<"Register For Position Name("<<poseCount+1<<") : ";
                cin.get();
                getline(cin,poseName[poseCount]);
                cout<<"Register For Position Type("<<poseCount+1<<") : ";
                getline(cin,poseType[poseCount]);
                cout<<"Successfully Added("<<poseName[poseCount]<<")\n";
                poseCount++;

                cout<<"Add More? (y/n) : ";
                cin>>more;
                if(more=='n') break;
            }
        }
        void createPosition(){
            cout<<"Enter Position Name : ";
            cin.get();
            getline(cin,name);
            POSITION++;
            addPosition();
        }
        void displayPosition(){
            cout<<setw(20)<<name<<endl;
            for(int i=0; i<poseCount; i++){
                cout<<setw(25)<<""
                    <<setw(20)<<poseType[i]
                    <<setw(20)<<poseName[i]
                    <<endl;
            }
        }
};
void displayTrainingPlans(TrainingPlan plans[]);
void displayYogaPositions(Position poses[]);
void displayCustomers(Customer customers[]);

int main(){
    int menuCode;
    
    Position poses[5];
    string basicPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string basicPoseNames[10] ={"Archer Pose","Dolphin Pose","Frog Pose","Fallen Triangle","Big Toe Pose","Lion Pose","Airplane Pose","Side Lunge","Side Reclining","Bird Dog Pose"};
    Position pose1("BASIC",basicPoseType,basicPoseNames,10);
    
    string imPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string imPoseNames[10] ={"Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge","Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position pose2("INTERMEDIATE",imPoseType,imPoseNames,10);
    
    poses[0] = pose1;
    poses[1] = pose2;
    
    TrainingPlan plans[7];
    TrainingPlan basic("BASIC",3,20000);
    TrainingPlan inter("INTERMEDIATE",3,30000);
    TrainingPlan advan("ADVANCED",2,50000);
    plans[0] = basic;
    plans[1] = inter;
    plans[2] = advan;

    Customer customers[50];
    int c1Private[4] = {1,1,3,2};
    bool c1OnOff[4] = {true,false,true,true};
    int c2Private[4] = {1,1,3,2};
    bool c2OnOff[4] = {true,true,true,false};
    int c3Private[4] = {1,1,3,2};
    bool c3OnOff[4] = {true,true,false,true};
    int c4Private[4] = {1,1,3,2};
    bool c4OnOff[4] = {false,false,true,true};
    int c5Private[4] = {1,1,3,2};
    bool c5OnOff[4] = {true,false,false,true};
    
    Customer c1("Lucia",plans[0],55,c1Private,c1OnOff);
    Customer c2("Lu Lu",plans[0],55,c2Private,c2OnOff);
    Customer c3("Ryan",plans[0],55,c3Private,c3OnOff);
    Customer c4("Kelly",plans[0],55,c4Private,c4OnOff);
    Customer c5("Brandon",plans[0],55,c5Private,c5OnOff);
    customers[0] = c1;
    customers[1] = c2;
    customers[2] = c3;
    customers[3] = c4;
    customers[4] = c5;

    menuLabel:
    cout<<"Welcome from Amazing Sport Yoga System !"<<endl
        <<setw(20)<<"1. Check The Training Plan"<<endl
        <<setw(15)<<"2. Customers"<<endl
        <<setw(20)<<"0. Quit \n";
    cin>>menuCode;
    if(menuCode==1) {
        trainingPlanScreenLabel:
        int trainingMenuCode = 0;
        cout<<"1. Add a training plan.\n2. Show all training plans.\n3. Update a training plan.\n4. Add a yoga plan.\n5. Display yoga plans.\n6. Add yoga poses.\n0. Return to main screen.\n";
        cin>>trainingMenuCode;
      
        if(trainingMenuCode < 0 || trainingMenuCode > 6) goto trainingPlanScreenLabel;
        if(trainingMenuCode == 0) goto menuLabel;
        else if(trainingMenuCode == 1) plans[PLAN].setPlan(plans);
        else if(trainingMenuCode == 2) displayTrainingPlans(plans);
        else if(trainingMenuCode == 3) {
            int index = 0;
            displayTrainingPlans(plans);
            cout<<"Enter number to update : ";
            cin>>index;
            plans[index-1].updatePlan();
        }
        else if(trainingMenuCode == 4) poses[POSITION].createPosition();
        else if(trainingMenuCode == 5) displayYogaPositions(poses);
        else if(trainingMenuCode == 6) {
            int index = 0;
            displayYogaPositions(poses);
            cout<<"\nEnter yoga plan index to add : ";
            cin>>index;
            poses[index-1].addPosition();
        }
        goto trainingPlanScreenLabel;
    } 
    else if(menuCode==2){
        customerScreenLabel:
        int customerScreenCode = 0;
        cout<<"1. Register a new customer.\n2. View all customers.\n3. Update customer info.\n4. Calculate costs for the customer.\n0. Return to main screen. \n";
        cin>>customerScreenCode;
        if(customerScreenCode < 0 || customerScreenCode > 4) goto customerScreenLabel;
      
        if(customerScreenCode == 0) goto menuLabel;
        else if(customerScreenCode == 1) {
            string plan = customers[CUSTOMER].setCustomer(plans);
            if(plan == "INTERMEDIATE") customers[CUSTOMER-1].addLearntPoses(basicPoseNames);
            else if(plan == "ADVANCED") customers[CUSTOMER-1].addLearntPoses(imPoseNames);
        }
        else if(customerScreenCode == 2) displayCustomers(customers);
        else if(customerScreenCode == 3) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to update : ";
            cin>>index;
            string plan = customers[index-1].updateCustomer(plans);
            if(plan == "INTERMEDIATE") customers[index-1].addLearntPoses(basicPoseNames);
            else if(plan == "ADVANCED") customers[index-1].addLearntPoses(imPoseNames);
        }
        else if(customerScreenCode == 4) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to calculate costs : ";
            cin>>index;
            customers[index-1].displayCustomerDetails();
        }
        goto customerScreenLabel;
    }
    else if(menuCode==0) return 0;
    else goto menuLabel;
}

void displayTrainingPlans(TrainingPlan plans[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Plan name"
        <<setw(20)<<"Session per week"
        <<setw(15)<<"Fees per week"
        <<endl;
    for(int i=0; i<PLAN; i++) {
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
}

void displayYogaPositions(Position poses[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Position names"
        <<setw(20)<<"Pose type"
        <<setw(20)<<"Pose name"
        <<endl;
    for(int i=0; i<POSITION; i++) {
        cout<<setw(5)<<i+1;
        poses[i].displayPosition();
        cout<<endl;
    }
}

void displayCustomers(Customer customers[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Customer name"
        <<setw(20)<<"Training plan"
        <<setw(10)<<"Learnt poses count"
        <<setw(20)<<"Cost(current month"
        <<endl;
    for(int i=0; i<CUSTOMER; i++) {
        cout<<setw(5)<<i+1;
        customers[i].displayCustomer();
        cout<<endl;
    }
}
