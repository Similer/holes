#include "stdafx.h"
//// holes.cpp : Defines the entry point for the console application.
////
//
//#include "stdafx.h"
//
//#include "../protobuf/gen/PDL.pb.h"
//
//
//#define BUFSIZE 1024
//
//void CALLBACK CompletionRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
//void CALLBACK CompletionRoutine2(DWORD error, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
//void ErrorHandling(char *message);
//
//WSABUF databuf[10];
//char buf[10][BUFSIZE];
//DWORD recvBytes[10];
//SOCKET listenSocket, clientSocket[10];
//
//struct MyOverlapped
//{
//	WSAOVERLAPPED overlapped;
//	int index;
//};
//
//MyOverlapped overlapped[10];
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//
//	WSADATA wsaData;
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//	{
//		std::cout << "something is wrong" << std::endl;
//		return -1;
//	}
//
//	SOCKADDR_IN servAddr, clientAddr[10];
//
//
//
//	int nowConnection = 0;
//
//	int sendAddrSize;
//	int index;
//	DWORD flags = 0;
//
//	listenSocket = WSASocket(PF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
//	if (listenSocket == INVALID_SOCKET)
//	{
//		std::cout << "listenSocket is wrong" << std::endl;
//		return -1;
//	}
//
//	memset(&servAddr, 0, sizeof(servAddr));
//	servAddr.sin_family = AF_INET;
//	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	servAddr.sin_port = htons(7004);
//
//	if (bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
//	{
//		std::cout << "bind is wrong" << std::endl;
//		return -1;
//	}
//
//	if (listen(listenSocket, 5) == SOCKET_ERROR)
//	{
//		std::cout << "listen is wrong" << std::endl;
//		return -1;
//	}
//
//	while (1)
//	{
//		int szClientAddr = sizeof(clientAddr[nowConnection]);
//		clientSocket[nowConnection] = accept(listenSocket, (SOCKADDR*)&clientAddr[nowConnection], &szClientAddr);
//		int nowIndex = nowConnection;
//		nowConnection++;
//
//		if (clientSocket[nowIndex] == INVALID_SOCKET)
//		{
//			std::cout << "accept is wrong" << std::endl;
//			return -1;
//		}
//
//		overlapped[nowIndex].index = nowIndex;
//		memset(&overlapped[nowIndex].overlapped, 0, sizeof(overlapped[nowIndex].overlapped));
//		databuf[nowIndex].len = BUFSIZE - 1;
//		databuf[nowIndex].buf = buf[nowIndex];
//
//		flags = 0;
//		memset(&overlapped[nowIndex].overlapped, 0, sizeof(overlapped[nowIndex].overlapped));
//		memset(&buf[nowIndex], 0, sizeof(buf[nowIndex]));
//
//		databuf[nowIndex].len = BUFSIZE - 1;
//		databuf[nowIndex].buf = buf[nowIndex];
//
//		if (WSARecv(clientSocket[nowIndex], &databuf[nowIndex], 1, &recvBytes[nowIndex], &flags, &overlapped[nowIndex].overlapped, CompletionRoutine) == SOCKET_ERROR)
//		{
//			auto error = WSAGetLastError();
//			if (error != WSA_IO_PENDING)
//			{
//				std::cout << "WSARecv is wrong" << std::endl;
//				return -1;
//			}
//		}
//	}
//
//	WSACleanup();
//
//
//	return 0;
//}
//
//void CALLBACK CompletionRoutine(DWORD error, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
//{
//	if (error != 0)
//		std::cout << "CompletionRoutine is wrong" << std::endl;
//
//	MyOverlapped* my = (MyOverlapped*)lpOverlapped;
//
//	recvBytes[my->index] = szRecvBytes;
//	buf[my->index][szRecvBytes] = 0;
//	printf("%s \n", buf[my->index]);
//
//
//	flags = 0;
//	memset(&overlapped[my->index].overlapped, 0, sizeof(overlapped[my->index].overlapped));
//	memset(&buf[my->index], 0, sizeof(buf[my->index]));
//
//	databuf[my->index].len = BUFSIZE - 1;
//	databuf[my->index].buf = buf[my->index];
//
//	if (WSARecv(clientSocket[my->index], &databuf[my->index], 1, &recvBytes[my->index], &flags, &overlapped[my->index].overlapped, CompletionRoutine) == SOCKET_ERROR)
//	{
//		auto error = WSAGetLastError();
//		if (error != WSA_IO_PENDING)
//		{
//			std::cout << "WSARecv is wrong" << std::endl;
//			return;
//		}
//	}
//}
//
//void CALLBACK CompletionRoutine2(DWORD error, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
//{
//	if (error != 0)
//		std::cout << "CompletionRoutine is wrong" << std::endl;
//
//	MyOverlapped* my = (MyOverlapped*)lpOverlapped;
//
//	recvBytes[my->index] = szRecvBytes;
//	buf[my->index][szRecvBytes] = 0;
//	printf("%s \n", buf[my->index]);
//
//
//	flags = 0;
//	memset(&overlapped[my->index].overlapped, 0, sizeof(overlapped[my->index].overlapped));
//	memset(&buf[my->index], 0, sizeof(buf[my->index]));
//
//	databuf[my->index].len = BUFSIZE - 1;
//	databuf[my->index].buf = buf[my->index];
//
//	if (WSASend(clientSocket[my->index], &databuf[my->index], 1, &recvBytes[my->index], &flags, &overlapped[my->index].overlapped, CompletionRoutine) == SOCKET_ERROR)
//	{
//		auto error = WSAGetLastError();
//		if (error != WSA_IO_PENDING)
//		{
//			std::cout << "WSARecv is wrong" << std::endl;
//			return;
//		}
//	}
//}