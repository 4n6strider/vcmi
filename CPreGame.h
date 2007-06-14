#include "SDL.h"
#include "CSemiDefHandler.h"
#include "CSemiLodHandler.h"
#include "CPreGameTextHandler.h" 
class CPreGame;
extern CPreGame * CPG;
typedef void(CPreGame::*ttt)();
template <class T=ttt> struct Button
{
	int type; // 1=yes; 2=no
	SDL_Rect pos;
	T fun;
	CSemiDefHandler* imgs;
	Button(int Type, SDL_Rect Pos, T Fun,CSemiDefHandler* Imgs):imgs(Imgs),type(Type),pos(Pos),fun(Fun){};
	Button(){};
};
class CPreGame
{
public:
	std::vector<Button<> > btns;
	CPreGameTextHandler * preth ;
	SDL_Rect * currentMessage;	
	SDL_Surface * behindCurMes;
	CSemiDefHandler *ok, *cancel;
	enum EState { //where are we?
		mainMenu, newGame, loadGame, ScenarioList
	} state;
	struct menuItems { 
		SDL_Surface * background;
		CSemiDefHandler *newGame, *loadGame, *highScores,*credits, *quit;
		SDL_Rect lNewGame, lLoadGame, lHighScores, lCredits, lQuit;
		ttt fNewGame, fLoadGame, fHighScores, fCredits, fQuit;
		int highlighted;//0=none; 1=new game; 2=load game; 3=high score; 4=credits; 5=quit
	} * ourMainMenu, * ourNewMenu;
	std::string map; //selected map
	std::vector<CSemiLodHandler *> handledLods; 
	CPreGame(); //c-tor
	std::string buttonText(int which);
	menuItems * currentItems();
	void quitAskBox();
	void quit(){exit(0);};  
	void initNewMenu(); 
	void showNewMenu();  
	void showMainMenu();  
	void runLoop(); // runs mainloop of PreGame
	void initMainMenu(); //loads components for main menu
	void highlightButton(int which, int on);
	void showCenBox (std::string data);
	void showAskBox (std::string data, void(*f1)(),void(*f2)());
	void hideBox ();
};