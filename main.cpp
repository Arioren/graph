#include <iostream>
#include <list>
#include <string>

#include "AcademicPlanAnalyzer.h"
#include "SocialNetworkAnalyzer.h"

using namespace std;

void runAcademicAnalyzer() {
    string path;
    cout << "Enter path to academic plan file: ";
    cin >> path;

    AcademicPlanAnalyzer analyzer(path);

    cout << "\nAcademicPlanAnalyzer menu\n";
    cout << "1) hasCycle\n";
    cout << "2) minimalSemesters\n";
    cout << "q) quit\n";

    while (true) {
        cout << "Choice: ";
        char choice;
        cin >> choice;

        if (choice == 'q') return;

        if (choice == '1') {
            cout << (analyzer.hasCycle() ? "Cycle exists" : "No cycle") << endl;
        }
        else if (choice == '2') {
            cout << analyzer.minimalSemesters() << endl;
        }
    }
}

void runSocialNetworkAnalyzer() {
    string path;
    cout << "Enter path to social network file: ";
    cin >> path;

    SocialNetworkAnalyzer analyzer(path);

    cout << "\nSocialNetworkAnalyzer menu\n";
    cout << "1) mutualFriendsCount\n";
    cout << "2) suggestNewFriends\n";
    cout << "3) mostRemoteUser\n";
    cout << "q) quit\n";

    while (true) {
        cout << "Choice: ";
        char choice;
        cin >> choice;

        if (choice == 'q') return;

        if (choice == '1') {
            int userId, candidateId;
            cout << "userId: ";
            cin >> userId;
            cout << "candidateId: ";
            cin >> candidateId;
            cout << analyzer.mutualFriendsCount(userId, candidateId) << endl;
        }
        else if (choice == '2') {
            int userId, k;
            cout << "userId: ";
            cin >> userId;
            cout << "k: ";
            cin >> k;

            list<int> suggestions = analyzer.suggestNewFriends(userId, k);
            for (list<int>::const_iterator it = suggestions.begin(); it != suggestions.end(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        }
        else if (choice == '3') {
            int userId;
            cout << "userId: ";
            cin >> userId;
            cout << analyzer.mostRemoteUser(userId) << endl;
        }
    }
}

int main() {
    cout << "Which analyzer do you want to test?\n";
    cout << "1) AcademicPlanAnalyzer\n";
    cout << "2) SocialNetworkAnalyzer\n";
    cout << "Choice (1/2): ";

    char choice;
    cin >> choice;

    if (choice == '1') runAcademicAnalyzer();
    if (choice == '2') runSocialNetworkAnalyzer();

    return 0;
}
