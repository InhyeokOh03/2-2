#include <iostream>

#include "IArticlePub.h"
#include "IArticleSub.h"


int main() {
    IArticlePub* dgistPub = new IArticlePub("DGIST");
    IArticlePub* bbcPub = new IArticlePub("BBC"); 
    IArticlePub* cnnPub = new IArticlePub("CNN"); 
    cout << endl;

    //Jenny subscribe DGIST, BBC
    IArticleSub* jennySub = new IArticleSub("Jenny", dgistPub); 
    bbcPub->NotifyAttach(jennySub);
    cout << endl;

    //Tom subscribe BBC, CNN
    IArticleSub* tomSub = new IArticleSub("Tom");
    bbcPub->NotifyAttach(tomSub); 
    cnnPub->NotifyAttach(tomSub);
    cout << endl;

    //Kate subscribe DGIST, BBC, CNN
    IArticleSub* kateSub = new IArticleSub("Kate", dgistPub);
    bbcPub->NotifyAttach(kateSub);
    kateSub->Attach(cnnPub);
    cout << endl;

    cout << "All Sub of (" << dgistPub->getPubName() << "," << dgistPub->getPubID() << "): ";
    dgistPub->PrintAllSub();

    cout << "All Sub of (" << bbcPub->getPubName() << "," << bbcPub->getPubID() << "): ";
    bbcPub->PrintAllSub();

    cout << "All Sub of (" << cnnPub->getPubName() << "," << cnnPub->getPubID() <<
    "): "; 

    cnnPub->PrintAllSub(); 
    cout << endl;

    kateSub->Detach(bbcPub); 
    cout << endl;

    cout << "All Pub of (" << jennySub->getSubName() << "," << jennySub->getSubID() << "): ";
    jennySub->PrintAllPub();

    cout << "All Pub of (" << tomSub->getSubName() << "," << tomSub->getSubID() << "): ";
    tomSub->PrintAllPub();

    cout << "All Pub of (" << kateSub->getSubName() << "," << kateSub->getSubID() << "): ";
    kateSub->PrintAllPub(); cout << endl;

    cout << "=========DGIST Notify ===========" << endl; 
    dgistPub->updatePubContents("Welcome New DGIST students"); 
    cout << endl;

    cout << "=========BBC Notify ===========" << endl; 
    bbcPub->updatePubContents("Mr. Son scored at Tottenham"); 
    cout << endl;

    cout << "=========CNN Notify ===========" << endl; 
    cnnPub->updatePubContents("New York city celebrates Christmas"); 
    cout << endl;

    cout << "=========DELETING [tomSub]===========" << endl; 
    delete tomSub;
    cout << endl;

    cout << "=========DGIST Notify ===========" << endl; 
    dgistPub->updatePubContents("Welcome New DGIST students"); 
    cout << endl;

    cout << "=========BBC Notify ===========" << endl; 
    bbcPub->updatePubContents("Mr. Son scored at Tottenham"); 
    cout << endl;

    cout << "=========CNN Notify ===========" << endl; 
    cnnPub->updatePubContents("New York city celebrates Christmas"); 
    cout << endl;

    cout << "=========Delete all others ===========" << endl; 
    delete dgistPub;
    delete bbcPub;
    delete cnnPub;
    delete jennySub;
    delete kateSub;
    
    return 0; 
}