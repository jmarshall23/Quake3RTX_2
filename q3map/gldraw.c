/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "qbsp.h"

// can't use the glvertex3fv functions, because the vec3_t fields
// could be either floats or doubles, depending on DOUBLEVEC_T

qboolean	drawflag;
vec3_t	draw_mins, draw_maxs;


#define	WIN_SIZE	512

void InitWindow (void)
{

}

void Draw_ClearWindow (void)
{
	

}

void Draw_SetRed (void)
{
	if (!drawflag)
		return;

	glColor3f (1,0,0);
}

void Draw_SetGrey (void)
{
	if (!drawflag)
		return;

	glColor3f (0.5,0.5,0.5);
}

void Draw_SetBlack (void)
{
	if (!drawflag)
		return;

	glColor3f (0,0,0);
}

void DrawWinding (winding_t *w)
{
	int		i;

	if (!drawflag)
		return;

	glColor4f (0,0,0,0.5);
	glBegin (GL_LINE_LOOP);
	for (i=0 ; i<w->numpoints ; i++)
		glVertex3f (w->p[i][0],w->p[i][1],w->p[i][2] );
	glEnd ();

	glColor4f (0,1,0,0.3);
	glBegin (GL_POLYGON);
	for (i=0 ; i<w->numpoints ; i++)
		glVertex3f (w->p[i][0],w->p[i][1],w->p[i][2] );
	glEnd ();

	glFlush ();
}

void DrawAuxWinding (winding_t *w)
{
	int		i;

	if (!drawflag)
		return;

	glColor4f (0,0,0,0.5);
	glBegin (GL_LINE_LOOP);
	for (i=0 ; i<w->numpoints ; i++)
		glVertex3f (w->p[i][0],w->p[i][1],w->p[i][2] );
	glEnd ();

	glColor4f (1,0,0,0.3);
	glBegin (GL_POLYGON);
	for (i=0 ; i<w->numpoints ; i++)
		glVertex3f (w->p[i][0],w->p[i][1],w->p[i][2] );
	glEnd ();

	glFlush ();
}

//============================================================

#define	GLSERV_PORT	25001

qboolean	wins_init;
int			draw_socket;

void GLS_BeginScene (void)
{
	WSADATA	winsockdata;
	WORD	wVersionRequested; 
	struct sockaddr_in	address;
	int		r;

	if (!wins_init)
	{
		wins_init = qtrue;

		wVersionRequested = MAKEWORD(1, 1); 

		r = WSAStartup (MAKEWORD(1, 1), &winsockdata);

		if (r)
			Error ("Winsock initialization failed.");

	}

	// connect a socket to the server

	draw_socket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (draw_socket == -1)
		Error ("draw_socket failed");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	address.sin_port = GLSERV_PORT;
	r = connect (draw_socket, (struct sockaddr *)&address, sizeof(address));
	if (r == -1)
	{
		closesocket (draw_socket);
		draw_socket = 0;
	}
}

void GLS_Winding (winding_t *w, int code)
{
	byte	buf[1024];
	int		i, j;

	if (!draw_socket)
		return;

	((int *)buf)[0] = w->numpoints;
	((int *)buf)[1] = code;
	for (i=0 ; i<w->numpoints ; i++)
		for (j=0 ; j<3 ; j++)
			((float *)buf)[2+i*3+j] = w->p[i][j];

	send (draw_socket, buf, w->numpoints*12+8, 0);
}

void GLS_EndScene (void)
{
	closesocket (draw_socket);
	draw_socket = 0;
}
