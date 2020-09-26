#include <iostream>
#include <vector>
#include <ctime> // For seeding
#include <string>

using namespace std;

// For getting the next card
int getNext ( ) {
	return (rand ( ) % 16) + 1;
}  

string getElements ( vector<int> set ) {
	// Sorting
	for ( int i = 0; i < set.size ( ); ++i ) {
		for ( int j = 0; j < set.size ( ); ++j ) {
			if ( set.at ( i ) < set.at ( j ) ) {
				int temp = set.at ( i );

				set.at ( i ) = set.at ( j );
				set.at ( j ) = temp;
			}
		}
	}
	

	// Printing
	string to_ret = "";
	
	for ( int i = 0; i < set.size ( ); ++i ) {
		
		if ( set.at ( i ) >= 10 ) {
			to_ret += to_string ( set.at ( i ) ) + " ";
		} else {
			to_ret += " " + to_string ( set.at ( i ) ) + " ";
		}
		
	}

	return to_ret;
}

int main()
{
	srand ( time ( NULL ) );
	char ans;

	do {

		vector<int> deadCards;
		vector<int> liveCards;

		int curScore = 0;
		int nextCard;
		bool isCardDead = false;
		
		// Populating the cards
		for ( int i = 0; i < 16; i++ ) {
			liveCards.push_back ( i + 1 );
		}

		while ( liveCards.size ( ) > 0 ) {
			isCardDead = false;
			nextCard = getNext ( );

			cout << "\nCurrent score: " << curScore << endl;
			cout << "Dead cards: " << getElements ( deadCards ) << endl;
			cout << "Live cards: " << getElements ( liveCards ) << endl;

			for ( int i = 0; i < deadCards.size ( ); ++i ) {
				if ( nextCard == deadCards.at ( i ) ) {
					isCardDead = true;
				}
			}

			if ( isCardDead ) {
				cout << "Next card: " << nextCard << " Dead" << endl;
				continue;
			}
			else {
				cout << "Next card: " << nextCard << endl;

				cout << "\nTake it [T] or Leave it [L]? ";
				cin >> ans;

				if ( tolower ( ans ) == 't' ) {
					curScore += nextCard;

					for ( int c = 0; c < liveCards.size ( ); ++c ) {
						for ( int i = 0; i < liveCards.size ( ); ++i ) {
							if ( liveCards.at ( i ) <= curScore ) {
								deadCards.push_back ( liveCards.at ( i ) );

								if ( i == 0 ) {
									liveCards.erase ( liveCards.begin ( ) );
								}
								else {
									liveCards.erase ( liveCards.begin ( ) + i );
								}
							}
						}
					}
				}
				else {
					for ( int i = 0; i < liveCards.size ( ); ++i ) {
						if ( liveCards.at ( i ) == nextCard ) {
							deadCards.push_back ( liveCards.at ( i ) );
							liveCards.erase ( liveCards.begin ( ) + i );
						}
					}
				}
			}
		}

		cout << "---------" << endl;
		cout << "FINAL SCORE: " << curScore << endl;
		cout << "---------" << endl;
		cout << "Would you like to play again? [Y]es or [N]o >>> ";
		cin >> ans;

	} while ( tolower ( ans ) != 'n' );
}
