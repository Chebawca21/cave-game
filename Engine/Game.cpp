/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	field("Maps\\map1.txt"),
	frog(field.GetFrogPos())
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	Vec2I dir = { 0, 0 };
	float dt = ft.Mark();
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir.y--;
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y++;
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x--;
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x++;
	}
	if (wnd.kbd.KeyIsPressed('C'))
	{
		field.SpawnMine();
		frog.TakeMine();
	}
	frog.Update(dir, dt, field);
	field.SetFrogPos(frog.GetPos());
	field.Update(dt);
}

void Game::ComposeFrame()
{
	field.Draw(gfx);
	frog.Draw({ 0, 0 }, gfx);
}
