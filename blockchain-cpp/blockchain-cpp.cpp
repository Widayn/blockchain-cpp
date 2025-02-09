﻿/*****************************************************************//**
 * \file   blockchain-cpp.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/dsa.h>
#include <memory>
#include <thread>
#include <map>
#include "Wallet.h"
#include "Transaction.h"
#include "BlockChain.h"
#include "Block.h"
#include "StringUtil.h"
#include "TransactionOutput.h"
#include "TCP_Server.h"
#include "TCP_Client.h"
#include "TCP_Head.h"
#include "TCP_Ping.h"
#include "ini.h"
#include "SaveChain.h"
#include "SaveWallet.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

void runServer(ini_t* config, BlockChain& blockChain) {
	int port;
	ini_sget(config, "basic", "port", "%d", &port);
	if (port < 1 || port > 65535) {
		StringUtil::printfError("Error port");
		return;
	}
	TCP_Server server = TCP_Server(port, blockChain);
}

int main()
{
	ini_t* config = ini_load("./config.ini");
	BlockChain blockChain = BlockChain();
	SaveChain::load(blockChain, config);
	Wallet wallet;
	SaveWallet::load(wallet, config);
	//thread Server(runServer, config, ref(blockChain));
	//Server.detach();

	//TCP_Ping ping = TCP_Ping();
	//ping.send("127.0.0.1", 8888);

	// = Wallet();
	//Wallet walletB = Wallet();
	//Wallet coinbase = Wallet();
	//map<string, TransactionOutput> UTXOs;
	//blockChain.genesisTransaction.sender = coinbase.publicKeyChar;
	//blockChain.genesisTransaction.reciepient = walletA.publicKeyChar;
	//blockChain.genesisTransaction.transactionId = "0";
	//blockChain.genesisTransaction.value = 100;
	//blockChain.genesisTransaction.generateSignature(coinbase.privateKeyChar);
	//blockChain.genesisTransaction.outputs.push_back(TransactionOutput(blockChain.genesisTransaction.reciepient, blockChain.genesisTransaction.value, blockChain.genesisTransaction.transactionId));
	//UTXOs.insert(pair<string, TransactionOutput>(blockChain.genesisTransaction.outputs[0].id, blockChain.genesisTransaction.outputs[0]));

	//StringUtil::printfInformation("Creating and Mining Genesis block... ");
	//Block genesis = Block("0");
	//genesis.addTransaction(blockChain.genesisTransaction, UTXOs);
	//blockChain.addBlock(genesis);

	while (1) {
		Block block = Block(blockChain.getTop().hash);
		blockChain.addBlock(block);
	}

	//Block block2 = Block(block1.hash);
	//StringUtil::printfSuccess("\nWalletA Attempting to send more funds (1000) than it has...");
	//block2.addTransaction(walletA.sendFunds(walletB.publicKeyChar, 1000, UTXOs), UTXOs);
	//blockChain.addBlock(block2);
	//StringUtil::printfSuccess("\nWalletA's balance is: " + to_string(walletA.getBalance(UTXOs)));
	//StringUtil::printfSuccess("WalletB's balance is: " + to_string(walletB.getBalance(UTXOs)));

	//Block block3 = Block(block2.hash);
	//StringUtil::printfSuccess("\nWalletB is Attempting to send funds (20) to WalletA...");
	//block3.addTransaction(walletB.sendFunds(walletA.publicKeyChar, 20, UTXOs), UTXOs);
	//StringUtil::printfSuccess("\nWalletA's balance is: " + to_string(walletA.getBalance(UTXOs)));
	//StringUtil::printfSuccess("WalletB's balance is: " + to_string(walletB.getBalance(UTXOs)));

	blockChain.isChainValid();
	SaveWallet::save(wallet, config);
	SaveChain::save(blockChain, config);

}