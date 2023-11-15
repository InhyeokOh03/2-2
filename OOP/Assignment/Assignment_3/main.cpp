#include <iostream>

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
        IArticleSub* sub_list[5]; 
        int numOfSub = 0; 
    
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
        //new
        virtual void Event() = 0;
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
        IArticlePub* pub_list[5];
        int numOfPub = 0;

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
    for (int i = 0; i < numOfSub; i++) {
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
    if (numOfSub > 0) {
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
    if (numOfSub > 0) {
        int winner_index = numOfSub - 1;
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
    numOfSub = 0;

    cout << "[Constructor] New Pub Created: (" << pub_name << "," << pub_id << ")" << endl;
}

IArticlePub::IArticlePub(const string name, const string con) : pub_name(name), recent_contents(con) {
    static_pub_counter++;
    pub_id = static_pub_counter;
    numOfSub = 0;

    cout << "[Constructor] New Pub Created: (" << pub_name << "," << pub_id << ")" << endl;
}

IArticlePub::~IArticlePub() {
    cout << "IArticlePub Destructor called" << endl;
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->DetachResponse(this);
    }
}

void IArticlePub::NotifyAttach(IArticleSub* subscriber) {
    // Are you subscriber?
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // Add neww subscriber
    if (numOfSub < 5) { // under 5
        sub_list[numOfSub] = subscriber;
        numOfSub++;

        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
        subscriber->AttachResponse(this);
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyAttachResponse(IArticleSub* subscriber) {
    // Are you subscriber?
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // Add new subscriber
    if (numOfSub < 5) { // under 5.
        sub_list[numOfSub] = subscriber;
        numOfSub++;
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyDetach(IArticleSub* subscriber) {
    bool found = false;

    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            found = true;

            for (int j = i; j < numOfSub - 1; j++) {
                sub_list[j] = sub_list[j + 1];
            }
            numOfSub--;
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

    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            found = true;

            for (int j = i; j < numOfSub - 1; j++) {
                sub_list[j] = sub_list[j + 1];
            }
            numOfSub--;
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
    for (int i = 0; i < numOfSub; i++) {
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
    return numOfSub;
}

void IArticlePub::PrintAllSub() {
    // cout << "All Sub of (" << pub_name << "," << pub_id << "): ";
    for (int i = 0; i < numOfSub; i++) {
        cout << "[" << sub_list[i]->getSubName() << "," << sub_list[i]->getSubID() << "]";
    }
    cout << endl;
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

    for (int i = 0; i < numOfPub; i++) {
        pub_list[i]->NotifyDetachResponse(this);
    }
}

void IArticleSub::Attach(IArticlePub* publisher) {
    pub_list[numOfPub] = publisher;
    numOfPub++;
    cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
    publisher->NotifyAttachResponse(this);
}

void IArticleSub::AttachResponse(IArticlePub* publisher) {
    pub_list[numOfPub] = publisher;
    numOfPub++;
cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
}   

void IArticleSub::Detach(IArticlePub* p_pub) {
    int index = -1;
    // remove
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < numOfPub - 1; i++) {
            pub_list[i] = pub_list[i + 1];
        }
        numOfPub--;
        cout << "[Sub] (" << sub_name << "," << sub_id << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;

        p_pub->NotifyDetachResponse(this);
    } else {
        cout << "Error: There is no publisher in subscribed list." << endl;
    }
}

void IArticleSub::DetachResponse(IArticlePub* p_pub) {
        int index = -1;
    
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < numOfPub - 1; i++) {
            pub_list[i] = pub_list[i + 1];
        }
        numOfPub--;
        cout << "[Sub] (" << sub_name << "," << sub_id << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;
    } else {
        cout << "Error: There is no publisher in subscribed list." << endl;
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
    return numOfPub;
}

void IArticleSub::PrintAllPub() {
    for (int i = 0; i < numOfPub; i++) {
        cout << "[" << pub_list[i]->getPubName() << "," << pub_list[i]->getPubID() << "]";
    }
    cout << endl;
}

//======================================Main=============================================
int main(){
    dgist_press* dgistPub = new dgist_press(string("this is dgist pub"));
    BBC* bbcPub = new BBC();
    CNN* cnnPub = new CNN();

    IArticlePub* cnnPub_upcasting = cnnPub;

    //Jenny subscribe DGIST, BBC
    IArticleSub* jennySub = new IArticleSub("Jenny", dgistPub);
    bbcPub->NotifyAttach(jennySub);

    //Tom subscribe BBC, CNN
    IArticleSub* tomSub = new IArticleSub("Tom");
    bbcPub->NotifyAttach(tomSub);
    cnnPub_upcasting->NotifyAttach(tomSub);

    //Kate subscribe DGIST, BBC, CNN
    IArticleSub* kateSub = new IArticleSub("Kate", dgistPub);
    bbcPub->NotifyAttach(kateSub);
    cnnPub_upcasting->NotifyAttach(kateSub);

    cout<<"All Sub of (" << dgistPub->getPubName() << "," << dgistPub->getPubID() << "): ";
    dgistPub->PrintAllSub();

    cout << "All Sub of (" << bbcPub->getPubName() << "," << bbcPub->getPubID() << "): "; bbcPub->PrintAllSub();

    cout << "All Sub of (" << cnnPub_upcasting->getPubName() << "," << cnnPub_upcasting->getPubID() << "): ";

    cnnPub_upcasting->PrintAllSub();

    bbcPub->Event();
    cnnPub_upcasting->Event();
    dgistPub->Event();
    dgistPub->CheerUp();
    kateSub->Detach(bbcPub);

    cout<<"All Pub of (" << jennySub->getSubName() << "," << jennySub->getSubID() << "): ";
    jennySub->PrintAllPub();

    cout << "All Pub of (" << tomSub->getSubName() << "," << tomSub->getSubID() << "): "; 
    tomSub->PrintAllPub();

    cout << "All Pub of (" << kateSub->getSubName() << "," << kateSub->getSubID() << "): "; 
    kateSub->PrintAllPub();

    cout << "=========DGIST Notify ===========" << endl;
    dgistPub->updatePubContents("Welcome New DGIST students");

    cout << "=========BBC Notify ===========" << endl;
    bbcPub->updatePubContents("Mr. Son scored at Tottenham");

    cout << "=========CNN Notify ===========" << endl;
    cnnPub_upcasting->updatePubContents("New York city celebrates Christmas");

    cout << "=========DELETING [tomSub]===========" << endl;
    delete tomSub;

    cout << "=========DGIST Notify ===========" << endl;
    dgistPub->updatePubContents("Welcome New DGIST students");

    cout << "=========BBC Notify ===========" << endl;
    bbcPub->updatePubContents("Mr. Son scored at Tottenham");

    cout << "=========CNN Notify ===========" << endl;
    cnnPub_upcasting->updatePubContents("New York city celebrates Christmas");

    cout << "=========Delete all others ===========" << endl;
    delete dgistPub;
    delete bbcPub;
    delete cnnPub;
    delete jennySub;

    delete kateSub;

    return 0; 
}