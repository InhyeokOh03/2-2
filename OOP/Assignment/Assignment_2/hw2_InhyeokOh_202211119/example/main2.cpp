#include <iostream>

using namespace std;

class IArticleSub;
class IArticlePub;

// // Forward Declation
// void IArticlePub::DetachResponse(IArticleSub* subscriber);

class IArticlePub {
    private:
        string pub_name;
        int pub_id;
        string recent_contents;
        IArticleSub* sub_list[5];
        int numOfSub = 0;
        static int static_pub_counter;
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
};

class IArticleSub {
    private:
        string sub_name;
        int sub_id;
        string recent_article_contents; 
        IArticlePub* recent_article_pub; 
        IArticlePub* pub_list[5];
        int numOfPub = 0;
        static int static_sub_counter;
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
    // 1. 모든 구독자의 publisher 리스트(pub_list)에서 현재 Publisher 제거
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->DetachResponse(this);
    }

    // 2. 적절한 정보 출력
    cout << "IArticlePub 소멸자 호출됨" << endl;
}

void IArticlePub::NotifyAttach(IArticleSub* subscriber) {
    // 이미 구독자인지 확인
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // 새로운 구독자를 추가
    if (numOfSub < 5) { // 최대 5명의 구독자까지만 추가 가능
        sub_list[numOfSub] = subscriber;
        numOfSub++;

        // 대칭적인 연결 (Subscriber의 pub_list에도 Publisher 추가)
        subscriber->AttachResponse(this);

        // 알림 메시지 출력
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyAttachResponse(IArticleSub* subscriber) {
    // 이미 구독자인지 확인
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // 새로운 구독자를 추가
    if (numOfSub < 5) { // 최대 5명의 구독자까지만 추가 가능
        sub_list[numOfSub] = subscriber;
        numOfSub++;

        // 대칭적인 연결 (Subscriber의 pub_list에도 Publisher 추가)
        subscriber->Attach(this);

        // 알림 메시지 출력
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

            subscriber->Detach(this);

            cout << "[Detach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is detached from Pub (" << pub_name << "," << pub_id << ")" << endl;
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
    cout << "All Sub of (" << pub_name << "," << pub_id << "): ";
    for (int i = 0; i < numOfSub; i++) {
        cout << "[" << sub_list[i]->getSubName() << "," << sub_list[i]->getSubID() << "]";
    }
    cout << endl;
}

//======================================Sub 함수들==========================================

IArticleSub::IArticleSub(const string name) {
    static int static_sub_counter = 0;
    sub_name = name;
    sub_id = ++static_sub_counter;

    // 정보 출력 (원하는 출력 형식 참조)
    cout << "[Constructor] New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;
}

IArticleSub::IArticleSub(const string name, IArticlePub* articlePub) {
    static int static_sub_counter = 0;
    sub_name = name;
    sub_id = ++static_sub_counter;

    // 출판사를 구독자의 목록에 추가
    Attach(articlePub);
    
    // 정보 출력 (원하는 출력 형식 참조)
    cout << "[Constructor] New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;
}

IArticleSub::~IArticleSub() {
    // 모든 출판사의 구독자 목록에서 구독자 제거
    for (int i = 0; i < numOfPub; i++) {
        pub_list[i]->NotifyDetachResponse(this);
    }

    // 정보 출력
    cout << "[Sub] (" << sub_name << "," << sub_id << ") 해지" << endl;
}

void IArticleSub::Attach(IArticlePub* publisher) {
    // 출판사를 구독자의 목록에 추가
    pub_list[numOfPub] = publisher;
    numOfPub++;

    // 대칭적인 관계를 설정하기 위해 출판사에서도 구독자를 추가
    publisher->NotifyAttachResponse(this);
}

void IArticleSub::AttachResponse(IArticlePub* publisher) {
    // 출판사를 구독자의 목록에 추가
    pub_list[numOfPub] = publisher;
    numOfPub++;
}

void IArticleSub::Detach(IArticlePub* p_pub) {
    int index = -1;
    
    // 출판사를 구독자의 목록에서 찾아 제거
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        // 출판사를 제거하고 목록을 재조정
        for (int i = index; i < numOfPub - 1; i++) {
            pub_list[i] = pub_list[i + 1];
        }
        numOfPub--;
        
        // 대칭적인 관계를 설정하기 위해 출판사의 NotifyDetachResponse 함수 호출
        p_pub->NotifyDetachResponse(this);
    } else {
        // 출판사가 목록에 존재하지 않는 경우 오류 메시지 출력
        cout << "Error: 출판사가 구독자의 목록에 존재하지 않습니다." << endl;
    }
}

void IArticleSub::DetachResponse(IArticlePub* p_pub) {
    // int index = -1;
    // int numOfSub = p_pub->getSubSize();
    // int sub_list = p_pub.sub;
    // // 구독자를 출판사의 목록에서 찾아 제거
    // for (int i = 0; i < numOfSub; i++) {
    //     if (sub_list[i] == p_pub) {
    //         index = i;
    //         break;
    //     }
    // }

    // if (index != -1) {
    //     // 구독자를 제거하고 목록을 재조정
    //     for (int i = index; i < numOfSub - 1; i++) {
    //         sub_list[i] = sub_list[i + 1];
    //     }
    //     numOfSub--;
    // }

    this->Detach(p_pub);
}

void IArticleSub::Update(IArticlePub* publisher, const string contents) {
    recent_article_pub = publisher;
    recent_article_contents = contents;
    
    // 최신 정보를 출력하는 PrintContents() 함수 호출
    PrintContents();
}

void IArticleSub::PrintContents() {
    if (recent_article_pub != nullptr) {
        cout << "최신 기사 정보:" << endl;
        cout << "출판사: " << recent_article_pub->getPubName() << endl;
        cout << "내용: " << recent_article_contents << endl;
    } else {
        cout << "아직 최신 기사가 없습니다." << endl;
    }
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
    cout << "구독 중인 모든 출판사 목록: ";
    for (int i = 0; i < numOfPub; i++) {
        cout << "[" << pub_list[i]->getPubName() << "," << pub_list[i]->getPubID() << "]";
    }
    cout << endl;
}

//======================================Main=============================================

int main() {
    IArticlePub* dgistPub = new IArticlePub("DGIST");
    IArticlePub* bbcPub = new IArticlePub("BBC"); 
    IArticlePub* cnnPub = new IArticlePub("CNN"); 
    cout << endl; //OK

    //Jenny subscribe DGIST, BBC
    IArticleSub* jennySub = new IArticleSub("Jenny", dgistPub); 
    bbcPub->NotifyAttach(jennySub);
    cout << endl;

    // //Tom subscribe BBC, CNN
    // IArticleSub* tomSub = new IArticleSub("Tom");
    // bbcPub->NotifyAttach(tomSub); 
    // cnnPub->NotifyAttach(tomSub);
    // cout << endl;

    // //Kate subscribe DGIST, BBC, CNN
    // IArticleSub* kateSub = new IArticleSub("Kate", dgistPub);
    // bbcPub->NotifyAttach(kateSub);
    // kateSub->Attach(cnnPub);
    // cout << endl;

    // cout << "All Sub of (" << dgistPub->getPubName() << "," << dgistPub->getPubID() << "): ";
    // dgistPub->PrintAllSub();

    // cout << "All Sub of (" << bbcPub->getPubName() << "," << bbcPub->getPubID() << "): ";
    // bbcPub->PrintAllSub();

    // cout << "All Sub of (" << cnnPub->getPubName() << "," << cnnPub->getPubID() <<
    // "): "; 

    // cnnPub->PrintAllSub(); 
    // cout << endl;

    // kateSub->Detach(bbcPub); 
    // cout << endl;

    // cout << "All Pub of (" << jennySub->getSubName() << "," << jennySub->getSubID() << "): ";
    // jennySub->PrintAllPub();

    // cout << "All Pub of (" << tomSub->getSubName() << "," << tomSub->getSubID() << "): ";
    // tomSub->PrintAllPub();

    // cout << "All Pub of (" << kateSub->getSubName() << "," << kateSub->getSubID() << "): ";
    // kateSub->PrintAllPub(); cout << endl;

    // cout << "=========DGIST Notify ===========" << endl; 
    // dgistPub->updatePubContents("Welcome New DGIST students"); 
    // cout << endl;

    // cout << "=========BBC Notify ===========" << endl; 
    // bbcPub->updatePubContents("Mr. Son scored at Tottenham"); 
    // cout << endl;

    // cout << "=========CNN Notify ===========" << endl; 
    // cnnPub->updatePubContents("New York city celebrates Christmas"); 
    // cout << endl;

    // cout << "=========DELETING [tomSub]===========" << endl; 
    // delete tomSub;
    // cout << endl;

    // cout << "=========DGIST Notify ===========" << endl; 
    // dgistPub->updatePubContents("Welcome New DGIST students"); 
    // cout << endl;

    // cout << "=========BBC Notify ===========" << endl; 
    // bbcPub->updatePubContents("Mr. Son scored at Tottenham"); 
    // cout << endl;

    // cout << "=========CNN Notify ===========" << endl; 
    // cnnPub->updatePubContents("New York city celebrates Christmas"); 
    // cout << endl;

    // cout << "=========Delete all others ===========" << endl; 
    // delete dgistPub;
    // delete bbcPub;
    // delete cnnPub;
    // delete jennySub;
    // delete kateSub;
    
    return 0; 
}


