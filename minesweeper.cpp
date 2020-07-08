/*	Minesweeper_Clone
	
	David Waters
	07/03/2020
	Personal Projects
	Video Games
	Minesweeper

	olcConsoleGameEngine.h Copyright(C) javidx9

	David Waters, the author of this minesweeper clone,
	does not own any of the code for the game engine used 
	in the creation of this project. olcConsoleGameEngine.h
	is used with permission and any use of this software will
	do its utmost to adhere to the GNU GPLv3 license that it
	falls under. All credit for the olcConsoleGameEngine.h
	and the olcSpriteEditor (for creating the sprites) goes to javidx9.

	All code belonging to the recreation of the minesweeper
	clone, where applicaple, is owned by David Waters. Full
	and complete credit and recognition is due to him by any
	that use this code in any capacity. This includes use of
	any assets required by the game. All sprites created by
	David Waters using the olcSpriteEditor, courtesy of javidx9.


	Please enjoy :)
*/



#include <iostream>
#include <string>
#include <time.h>

using namespace std;

#include "olcConsoleGameEngine.h"

class minesweeper_clone : public olcConsoleGameEngine
{
public:
	minesweeper_clone()
	{
		m_sAppName = L"Minesweeper";
	}

private:

	struct sTile
	{
		bool bRevealed = false;		// Has the player revealed this tile?
		bool bIsMine = false;		// Is this tile a mine or not?
		bool bFlagged = false;		// Has the tile been flagged as a mine?
		int xPosition{ 0 };			// Tile's position in 2D map/grid
		int yPosition{ 0 };
		int mineNeighbors{ 0 };		// Number of mines as neighbors that the tile has adjacent to it
	};

	struct sText
	{
		wstring sPackage{ NULL };
		double dPosition = 0;
		double dSpeed = 0;
	};

	sText* text = nullptr;
	sTile* tiles = nullptr;
	int nMines = 40;
	int nMapWidth = 32;			// Might want to handle any size here? (Dynamic)
	int nMapHeight = 20;
	int adjuster = 6;	// Used to change where to start keeping track in the y axis

	olcSprite* spriteCoveredTile = nullptr;
	olcSprite* spriteRevealedTile = nullptr;
	olcSprite* spriteFlag = nullptr;
	olcSprite* spriteMine = nullptr;
	olcSprite* spriteTrippedMine = nullptr;
	olcSprite* spriteOne = nullptr;
	olcSprite* spriteTwo = nullptr;
	olcSprite* spriteThree = nullptr;
	olcSprite* spriteFour = nullptr;
	olcSprite* spriteFive = nullptr;
	olcSprite* spriteSix = nullptr;
	olcSprite* spriteSeven = nullptr;
	olcSprite* spriteEight = nullptr;
	olcSprite* spriteM = nullptr;
	olcSprite* spriteI = nullptr;
	olcSprite* spriteN = nullptr;
	olcSprite* spriteE = nullptr;
	olcSprite* spriteS = nullptr;
	olcSprite* spriteW = nullptr;
	olcSprite* spriteP = nullptr;
	olcSprite* spriteR = nullptr;

protected:

	virtual bool OnUserCreate()
	{
		// Create new sprites so the olcConsoleGameEngine.h can use them
		spriteCoveredTile = new olcSprite(L"assets/covered_tile.spr");
		spriteRevealedTile = new olcSprite(L"assets/revealed_tile.spr");
		spriteFlag = new olcSprite(L"assets/flag.spr");
		spriteMine = new olcSprite(L"assets/mine.spr");
		spriteTrippedMine = new olcSprite(L"assets/tripped_mine.spr");
		spriteOne = new olcSprite(L"assets/one.spr");
		spriteTwo = new olcSprite(L"assets/two.spr");
		spriteThree = new olcSprite(L"assets/three.spr");
		spriteFour = new olcSprite(L"assets/four.spr");
		spriteFive = new olcSprite(L"assets/five.spr");
		spriteSix = new olcSprite(L"assets/six.spr");
		spriteSeven = new olcSprite(L"assets/seven.spr");
		spriteEight = new olcSprite(L"assets/eight.spr");
		spriteM = new olcSprite(L"assets/M.spr");
		spriteI = new olcSprite(L"assets/I.spr");
		spriteN = new olcSprite(L"assets/N.spr");
		spriteE = new olcSprite(L"assets/E.spr");
		spriteS = new olcSprite(L"assets/S.spr");
		spriteW = new olcSprite(L"assets/W.spr");
		spriteP = new olcSprite(L"assets/P.spr");
		spriteR = new olcSprite(L"assets/R.spr");

		// Create a "2D" array of tiles
		tiles = new sTile[nMapWidth * nMapHeight];
		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
			{
				tiles[y * nMapWidth + x].xPosition = x;
				tiles[y * nMapWidth + x].yPosition = y;
				tiles[y * nMapWidth + x].bRevealed = false;
				tiles[y * nMapWidth + x].bIsMine = false;
				tiles[y * nMapWidth + x].bFlagged = false;
;			}

		placeMines(tiles, nMapWidth * nMapHeight);

		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
				tiles[y * nMapWidth + x].mineNeighbors = checkNeighbors(x, y);

		text = new sText;
		text->sPackage = L"REPEEWSENIM";	// MINESWEEPER spelled backwards
		text->dSpeed = 4;

		return true;
	}

	void placeMines(sTile tiles[], int size)
	{
		int x = 3; //rand() % nMapWidth;
		int y = 3; //rand() % nMapHeight;
		int mineCounter = 0;

		while (mineCounter < nMines)
		{
			if (!(tiles[y * nMapWidth + x].bIsMine))
			{
				if (y > nMapHeight / adjuster)
				{
					tiles[y * nMapWidth + x].bIsMine = true;
					mineCounter++;
				}
			}
			x = rand() % nMapWidth;
			y = rand() % nMapHeight;
		}

		return;
	}

	// Determine the number of mine neighbors a tile has and return that value
	// Handles edge cases such as corners and walls
	int checkNeighbors(int xpos, int ypos)
	{
		int neighbor_count = 0;

		// Top side check
		if (ypos - 1 > 0)
			if (tiles[(ypos - 1) * nMapWidth + xpos].bIsMine)
				neighbor_count++;
		// Right side check
		if (xpos + 1 < nMapWidth)
			if (tiles[ypos * nMapWidth + (xpos + 1)].bIsMine)
				neighbor_count++;
		// Bottom side check
		if (ypos + 1 < nMapHeight)
			if (tiles[(ypos + 1) * nMapWidth + xpos].bIsMine)
				neighbor_count++;
		// Left side check
		if (xpos - 1 > 0)
			if (tiles[ypos * nMapWidth + (xpos - 1)].bIsMine)
				neighbor_count++;
		// Top left corner check
		if (ypos - 1 > 0 && xpos - 1 > 0)
			if (tiles[(ypos - 1) * nMapWidth + (xpos - 1)].bIsMine)
				neighbor_count++;
		// Top right corner check
		if (ypos - 1 > 0 && xpos + 1 < nMapWidth)
			if (tiles[(ypos - 1) * nMapWidth + (xpos + 1)].bIsMine)
				neighbor_count++;
		// Bottom left corner check
		if (ypos + 1 < nMapHeight && xpos - 1 > 0)
			if (tiles[(ypos + 1) * nMapWidth + (xpos - 1)].bIsMine)
				neighbor_count++;
		// Bottom right corner check
		if (ypos + 1 < nMapHeight && xpos + 1 < nMapWidth)
			if (tiles[(ypos + 1) * nMapWidth + (xpos + 1)].bIsMine)
				neighbor_count++;

		return neighbor_count;
	}

	// Checks the surrounding neighbors, including diagonals, and looks for any
	// empty (i.e. 0) cases. If a neighbor is 0, changes it's status to revealed
	// and checks that tile as well
	void openNeighbors(sTile tile[], int xpos, int ypos)
	{
		// If there is an "empty" tile, reveal it and check surrounding neighbors
		if (tile[ypos * nMapWidth + xpos].mineNeighbors == 0 && !tile[ypos * nMapWidth + xpos].bIsMine && !tile[ypos * nMapWidth + xpos].bRevealed)
		{
			tile[ypos * nMapWidth + xpos].bRevealed = true;

			// Top side check
			if (ypos - 1 > 0)
			{
				openNeighbors(tile, xpos, ypos - 1);
			}
			// Right side check
			if (xpos + 1 < nMapWidth)
			{
				openNeighbors(tile, xpos + 1, ypos);
			}
			// Bottom side check
			if (ypos + 1 < nMapHeight)
			{
				openNeighbors(tile, xpos, ypos + 1);
			}
			// Left side check
			if (xpos - 1 > 0)
			{
				openNeighbors(tile, xpos - 1, ypos);
			}

			// Top left corner check
			if (ypos - 1 > 0 && xpos - 1 > 0)
				tile[(ypos - 1) * nMapWidth + (xpos - 1)].bRevealed = true;
			// Top right corner check
			if (ypos - 1 > 0 && xpos + 1 < nMapWidth)
				tile[(ypos - 1) * nMapWidth + (xpos + 1)].bRevealed = true;
			// Bottom left corner check
			if (ypos + 1 < nMapHeight && xpos - 1 > 0)
				tile[(ypos + 1) * nMapWidth + (xpos - 1)].bRevealed = true;
			// Bottom right corner check
			if (ypos + 1 < nMapHeight && xpos + 1 < nMapWidth)
				tile[(ypos + 1) * nMapWidth + (xpos + 1)].bRevealed = true;
		}
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		int nTileSize = 8;			// Tiles are 7 pixel sizes big, using 8 to give a nice black finish
		int nTileBorder = 1;		// Spacing between tiles
		int textAdjuster = 14;		// Spacing for "MINESWEEPER" wrapping text

		// Using integer division to place cursor position in tile space
		int nSelectedTileX = m_mousePosX / nTileSize;
		int nSelectedTileY = m_mousePosY / nTileSize;

		// First clear the screen to empty
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// Minesweeper text in the top circulating
		text->dPosition += fElapsedTime * text->dSpeed;
		for (int i = 0; i < text->sPackage.size(); i++)
		{
			//Draw(((int)text->dPosition - i) % ScreenWidth(), ScreenHeight() / 16, text->sPackage[text->sPackage.size() - i - 1], FG_WHITE);

			// Draw out the word "MINESWEEPER"
			if (text->sPackage[i] == 'M')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteM);
			else if (text->sPackage[i] == 'I')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteI);
			else if (text->sPackage[i] == 'N')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteN);
			else if (text->sPackage[i] == 'E')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteE);
			else if (text->sPackage[i] == 'S')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteS);
			else if (text->sPackage[i] == 'W')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteW);
			else if (text->sPackage[i] == 'P')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteP);
			else if (text->sPackage[i] == 'R')
				DrawSprite((((int)text->dPosition - i) * nTileSize) % ScreenWidth(), ScreenHeight() / textAdjuster, spriteR);
		}

		// Right here would go that extra "button" you are thinking about


		// Handle mouse input for selecting tiles
		if (m_mouse[0].bReleased)
			if (nSelectedTileX >= 0 && nSelectedTileX < nMapWidth)
				if (nSelectedTileY >= nMapHeight / adjuster && nSelectedTileY < nMapHeight)
					if (!(tiles[nSelectedTileY * nMapWidth + nSelectedTileX].bFlagged))
					{
						if (tiles[nSelectedTileY * nMapWidth + nSelectedTileX].mineNeighbors != 0)
							tiles[nSelectedTileY * nMapWidth + nSelectedTileX].bRevealed = true;
						else if (tiles[nSelectedTileY * nMapWidth + nSelectedTileX].bIsMine)
							tiles[nSelectedTileY * nMapWidth + nSelectedTileX].bRevealed = true;
						else
							openNeighbors(tiles, nSelectedTileX, nSelectedTileY);
					}

		// Handle mouse input for flagging tiles -- needs help, won't change back to a covered tiles when hitting rmb again
		if (m_mouse[1].bReleased)
			if (nSelectedTileX >= 0 && nSelectedTileX < nMapWidth)
				if (nSelectedTileY >= nMapHeight / adjuster && nSelectedTileY < nMapHeight)
					tiles[nSelectedTileY * nMapWidth + nSelectedTileX].bFlagged = !tiles[nSelectedTileY * nMapWidth + nSelectedTileX].bFlagged;

		// Draw the appropriate sprites in their correct locations
		for (int x = 0; x < nMapWidth; x++)
			for (int y = nMapHeight / adjuster + 1; y < nMapHeight; y++)
			{
				if (tiles[y * nMapWidth + x].bRevealed)
				{
					if (tiles[y * nMapWidth + x].bIsMine)	// Right here, might want another helper function to handle game over case -- player selected a mine, gg
						DrawSprite(x * nTileSize, y * nTileSize, spriteTrippedMine);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 0)
						DrawSprite(x * nTileSize, y * nTileSize, spriteRevealedTile);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 1)
						DrawSprite(x * nTileSize, y * nTileSize, spriteOne);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 2)
						DrawSprite(x * nTileSize, y * nTileSize, spriteTwo);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 3)
						DrawSprite(x * nTileSize, y * nTileSize, spriteThree);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 4)
						DrawSprite(x * nTileSize, y * nTileSize, spriteFour);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 5)
						DrawSprite(x * nTileSize, y * nTileSize, spriteFive);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 6)
						DrawSprite(x * nTileSize, y * nTileSize, spriteSix);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 7)
						DrawSprite(x * nTileSize, y * nTileSize, spriteSeven);
					else if (tiles[y * nMapWidth + x].mineNeighbors == 8)
						DrawSprite(x * nTileSize, y * nTileSize, spriteEight);
					else
					{
						cout << "This shouldn't have happened. . .\n";
						break;
					}
				}
				else
				{
					// This first if only for testing purposes...
					//if (tiles[y * nMapWidth + x].bIsMine)
						//DrawSprite(x * nTileSize, y * nTileSize, spriteMine);
					if (tiles[y * nMapWidth + x].bFlagged)
						DrawSprite(x * nTileSize, y * nTileSize, spriteFlag);
					else
						DrawSprite(x * nTileSize, y * nTileSize, spriteCoveredTile);
				}
			}

		// Add a highlight feature for current tile the mouse is hovering over
		if (m_mousePosX / nTileSize == nSelectedTileX && nSelectedTileX >= 0 && nSelectedTileX < nMapWidth)
			if (m_mousePosY / nTileSize == nSelectedTileY && nSelectedTileY > nMapHeight / adjuster && nSelectedTileY < nMapHeight)
			{
				Fill(nSelectedTileX * nTileSize, nSelectedTileY * nTileSize,
					(nSelectedTileX + 1) * nTileSize - nTileBorder, (nSelectedTileY + 1) * nTileSize - nTileBorder,
					PIXEL_THREEQUARTERS, FG_WHITE);
			}

		return true;
	}
};

int main()
{
	srand(time(NULL));
	minesweeper_clone game;
	//game.ConstructConsole(128, 80, 12, 12);
	game.ConstructConsole(256,160, 5, 5);
	game.Start();

	return 0;
}