#include <iostream>
#include <vector>

using namespace std;

class IArticleSub;
class IArticlePub;
// class dgist_press;

class IArticlePub {
    private:
        string pub_name;
        int pub_id;
        string recent_contents;
        static int static_pub_counter;
    //new
    protected:
        vector<IArticleSub*> sub_list;
    
    public:
        IArticlePub(const string name);
        IArticlePub(string name, const string con);
        ~IArticlePub();
        void NotifyAttach(IArticleSub* subscriber);
        void NotifyAttachResponse(IArticleSub* subscriber); 
        void NotifyDetach(IArticleSub* subscriber);
        void NotifyDetachResponse(IArticleSub* subscriber); 
        void updatePubContents(string c);
        void Notify();
        int getPubID();
        string getPubName();
        int getSubSize();
        void PrintAllSub();
        virtual void Event() = 0;

        IArticlePub& operator<<(const string& newContents);
};

class IArticleSub {
    private:
        string sub_name;
        int sub_id;
        string recent_article_contents; 
        IArticlePub* recent_article_pub; 
        static int static_sub_counter;
    //new
    protected:
        vector<IArticlePub*> pub_list;

    public:
        IArticleSub(string name);
        IArticleSub(string name, IArticlePub* articlePub); 
        ~IArticleSub();
        void Attach(IArticlePub* publisher);
        void AttachResponse(IArticlePub* publisher);
        void Detach(IArticlePub* p_pub);
        void DetachResponse(IArticlePub* p_pub);
        void Update(IArticlePub* publisher, const string contents); 
        void PrintContents();
        string getSubName();
        int getSubID();
        int getPubSize();
        void PrintAllPub();

        IArticleSub& operator>>(IArticlePub* newPub);
};

class dgist_press: public IArticlePub {
    public:
    dgist_press();
    dgist_press(const string con);
    void Event();
    void CheerUp();
    ~dgist_press();
};

dgist_press::dgist_press(): IArticlePub("DGIST") {
    cout << "dgist press constructor1 is called" << endl;
}

dgist_press::dgist_press(const string con): IArticlePub("DGIST", con) {
    cout << "dgist press constructor2 is called" << endl;
}

void dgist_press::Event() {
    cout << "The Event is totally swindle" << endl;
}

void dgist_press::CheerUp() {
    for (int i = 0; i < sub_list.size(); i++) {
        sub_list[i]->Update(this, "I Love you guys");
    }
}

dgist_press::~dgist_press() {
    cout << "DGIST PRESS is destructed" << endl;
}

class BBC: public IArticlePub {
    public:
        BBC();
        BBC(const string con);
        void Advertisement();
        void Event();
        ~BBC();
};

BBC::BBC(): IArticlePub("BBC") {
    cout << "BBC constructor1 is called" << endl;
}

BBC::BBC(const string con): IArticlePub("BBC", con) {
    cout << "BBC constructor2 is called" << endl;
}

void BBC::Event() {
    if (sub_list.size() > 0) {
        int winner_index = 0;
        cout << "The Event winner is (" << sub_list[winner_index]->getSubName() << "," << sub_list[winner_index]->getSubID() << ")" << endl;
    } else {
        cout << "Error: No subscribers for the Event." << endl;
    }
}

void BBC::Advertisement() {
    cout << "BBC NEWS is coming soon!!" << endl;
}

BBC::~BBC() {
    cout << "BBC is destructed" << endl;
}

class CNN: public IArticlePub {
    public:
        CNN();
        CNN(const string con);
        void Event();
        ~CNN();
};

CNN::CNN():IArticlePub("CNN") {
    cout << "CNN constructor1 is called" << endl;
}

CNN::CNN(const string con): IArticlePub("CNN", con) {
    cout << "CNN constructor2 is called" << endl;
}

void CNN::Event() {
    if (sub_list.size() > 0) {
        int winner_index = sub_list.size() - 1;
        cout << "The Event winner is (" << sub_list[winner_index]->getSubName() << "," << sub_list[winner_index]->getSubID() << ")" << endl;
    } else {
        cout << "Error: No subscribers for the event." << endl;
    }
}

CNN::~CNN() {
    cout << "CNN is destructed" << endl;
}

int IArticleSub::static_sub_counter = 0;
int IArticlePub::static_pub_counter = 0;


//======================================Pub 함수들==========================================

IArticlePub::IArticlePub(const string name) : pub_name(name) {
    static_pub_counter++;
    pub_id = static_pub_counter;
    recent_contents = "";

    cout << "[Constructor] New Pub Created: (" << pub_name << "," << pub_id << ")" << endl;
}

IArticlePub::IArticlePub(const string name, const string con) : pub_name(name), recent_contents(con) {
    static_pub_counter++;
    pub_id = static_pub_counter;

    cout << "[Constructor] New Pub Created: (" << pub_name << "," << pub_id << ")" << endl;
}

IArticlePub::~IArticlePub() {
    cout << "IArticlePub Destructor called" << endl;
    for (int i = 0; i < sub_list.size(); i++) {
        sub_list[i]->DetachResponse(this);
    }
}

void IArticlePub::NotifyAttach(IArticleSub* subscriber) {
    // Are you subscriber?
    for (int i = 0; i < sub_list.size(); i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // Add neww subscriber
    if (sub_list.size() < 5) { // under 5
        sub_list.push_back(subscriber);


        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
        subscriber->AttachResponse(this);
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyAttachResponse(IArticleSub* subscriber) {
    for (int i = 0; i < sub_list.size(); i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }
    // Add new subscriber
    if (sub_list.size() < 5) { // under 5.
        sub_list.push_back(subscriber);
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyDetach(IArticleSub* subscriber) {
    bool found = false;

    for (int i = 0; i < sub_list.size(); i++) {
        if (sub_list[i] == subscriber) {
            found = true;

            for (int j = i; j < sub_list.size() - 1; j++) {
                sub_list[j] = sub_list[j + 1];
            }
            sub_list.pop_back();
            subscriber->DetachResponse(this);
            cout << "[Detach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is detached from Pub (" << pub_name << "," << pub_id << ")" << endl;
        }
    }
    if (!found) {
        cout << "Error: Subscriber " << subscriber->getSubName() << " is not in the publisher's subscriber list." << endl;
    }
}

void IArticlePub::NotifyDetachResponse(IArticleSub* subscriber) {
    bool found = false;

    for (int i = 0; i < sub_list.size(); i++) {
        if (sub_list[i] == subscriber) {
            found = true;

            for (int j = i; j < sub_list.size() - 1; j++) {
                sub_list[j] = sub_list[j + 1];
            }
            sub_list.pop_back();
            subscriber->DetachResponse(this);
            cout << "[Pub] (" << pub_name << "," << pub_id << ") detach [Sub] (" << subscriber->getSubName() << "," << subscriber->getSubID() << ")" << endl;
        }
    }
    if (!found) {
        cout << "Error: Subscriber " << subscriber->getSubName() << " is not in the publisher's subscriber list." << endl;
    }
}

void IArticlePub::updatePubContents(string c) {
    recent_contents = c;
    Notify();
}

void IArticlePub::Notify() {
    for (int i = 0; i < sub_list.size(); i++) {
        sub_list[i]->Update(this, recent_contents);
    }
}

int IArticlePub::getPubID() {
    return pub_id;
}

string IArticlePub::getPubName() {
    return pub_name;
}

int IArticlePub::getSubSize() {
    return sub_list.size();
}

void IArticlePub::PrintAllSub() {
    // cout << "All Sub of (" << pub_name << "," << pub_id << "): ";
    for (int i = 0; i < sub_list.size(); i++) {
        cout << "[" << sub_list[i]->getSubName() << "," << sub_list[i]->getSubID() << "]";
    }
    cout << endl;
}

IArticlePub& IArticlePub::operator<<(const string& newContents) {
    updatePubContents(newContents); // 내용 업데이트
    Notify(); // 모든 구독자에게 알림
    return *this;
}

//======================================Sub 함수들==========================================

IArticleSub::IArticleSub(const string name) {
    sub_name = name;
    sub_id = ++static_sub_counter;

    cout << "[Constructor]New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;
}

IArticleSub::IArticleSub(const string name, IArticlePub* articlePub) {
    sub_name = name;
    sub_id = ++static_sub_counter;
    cout << "[Constructor]New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;

    Attach(articlePub);
}

IArticleSub::~IArticleSub() {
    cout << "IArticleSub Destructor called" << endl;

    for (int i = 0; i < pub_list.size(); i++) {
        pub_list[i]->NotifyDetachResponse(this);
    }
}

void IArticleSub::Attach(IArticlePub* publisher) {
    for (const auto& pub : pub_list) {
        if (pub == publisher) {
            cout << "[ERROR]: already subscribes " << publisher->getPubName() << endl;
            return;
        }
    }

    pub_list.push_back(publisher);
    cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
    publisher->NotifyAttachResponse(this);
}

void IArticleSub::AttachResponse(IArticlePub* publisher) {
    pub_list.push_back(publisher);
cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
}   

void IArticleSub::Detach(IArticlePub* p_pub) {
    int index = -1;
    // remove
    for (int i = 0; i < pub_list.size(); i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        pub_list.erase(pub_list.begin() + index);
        cout << "[Sub] (" << sub_name << "," << sub_id << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;

        p_pub->NotifyDetachResponse(this);
    } else {
        cout << "Error: There is no publisher in subscribed list." << endl;
    }
}

void IArticleSub::DetachResponse(IArticlePub* p_pub) {
        int index = -1;
    
    auto it = find(pub_list.begin(), pub_list.end(), p_pub);
    if (it != pub_list.end()) {
        index = distance(pub_list.begin(), it);
    }
    if (index != -1) {
        pub_list.erase(pub_list.begin() + index);
        cout << "[Sub] (" << sub_name << "," << sub_id << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;
    } else {
        // cout << "Error: There is no publisher in subscribed list." << endl;
    }
}

void IArticleSub::Update(IArticlePub* publisher, const string contents) {
    recent_article_pub = publisher;
    recent_article_contents = contents;
    
    PrintContents();
}

void IArticleSub::PrintContents() {
    cout << "Sub (" << sub_name << "," << sub_id << ")'s latest subscribed news is \"" << recent_article_contents << "\" by " << recent_article_pub->getPubName() << endl;
}

string IArticleSub::getSubName() {
    return sub_name;
}

int IArticleSub::getSubID() {
    return sub_id;
}

int IArticleSub::getPubSize() {
    return pub_list.size();
}

void IArticleSub::PrintAllPub() {
    for (int i = 0; i < pub_list.size(); i++) {
        cout << "[" << pub_list[i]->getPubName() << "," << pub_list[i]->getPubID() << "]";
    }
    cout << endl;
}

IArticleSub& IArticleSub::operator>>(IArticlePub* newPub) {
    Attach(newPub); // 새로운 publisher를 구독자에 추가
    return *this;
}

//======================================Main=============================================
int main(){
    dgist_press* dgistPub = new dgist_press(string("this is dgist pub")); //ok
    BBC* bbcPub = new BBC(); //ok
    CNN* cnnPub = new CNN(); //ok

    //Jenny subscribe DGIST, BBC
    IArticleSub* jennySub = new IArticleSub("Jenny", dgistPub); //ok
    *jennySub >> bbcPub; //Operator Overloading

    //Tom subscribe BBC, CNN
    IArticleSub* tomSub = new IArticleSub("Tom");
    *tomSub >> bbcPub; //Operator Overloading
    *tomSub >> cnnPub; //Operator Overloading

    //Kate subscribe DGIST, BBC, CNN
    IArticleSub* kateSub = new IArticleSub("Kate", dgistPub);
    *kateSub >> bbcPub; //Operator Overloading
    *kateSub >> bbcPub; //Operator Overloading
    *kateSub >> cnnPub; //Operator Overloading

    cout << "All Sub of (" << dgistPub->getPubName() << "," << dgistPub->getPubID() << "):";
    dgistPub->PrintAllSub();

    cout << "All Sub of (" << bbcPub->getPubName() << "," << bbcPub->getPubID() << "): ";
    bbcPub->PrintAllSub();

    cout << "All Sub of (" << cnnPub->getPubName() << "," << cnnPub->getPubID() << "): ";
    cnnPub->PrintAllSub();

    bbcPub->Event();
    dgistPub->CheerUp(); //done
    kateSub->Detach(bbcPub); 
    
    cout << "All Pub of (" << jennySub->getSubName() << "," << jennySub->getSubID() << "):";
    jennySub->PrintAllPub();

    cout << "All Pub of (" << tomSub->getSubName() << "," << tomSub->getSubID() << "): ";
    tomSub->PrintAllPub();

    cout << "All Pub of (" << kateSub->getSubName() << "," << kateSub->getSubID() << "): ";
    kateSub->PrintAllPub();

    cout << "=========DGIST Notify ===========" << endl;
    *dgistPub << "Welcome New DGIST students"; //Operator Overloading

    cout << "=========BBC Notify ===========" << endl;
    *bbcPub << "Mr. Son scored at Tottenham"; //Operator Overloading

    cout << "=========CNN Notify ===========" << endl;
    *cnnPub << "New York city celebrates Christmas"; //Operator Overloading

    cout << "=========DELETING [tomSub]===========" << endl;
    delete tomSub;

    cout << "=========DGIST Notify ===========" << endl;
    *dgistPub << "Welcome New DGIST students"; //Operator Overloading

    cout << "=========BBC Notify ===========" << endl;
    *bbcPub << "Mr. Son scored at Tottenham"; //Operator Overloading

    cout << "=========CNN Notify ===========" << endl;
    *cnnPub << "New York city celebrates Christmas"; //Operator Overloading

    cout << "=========Delete all others ===========" << endl;
    delete dgistPub;
    delete bbcPub;
    delete cnnPub;
    delete jennySub;
    //delete tomSub;
    delete kateSub;

    return 0;
}