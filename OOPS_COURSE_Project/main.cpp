#include<ctime>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

//Transaction Data
struct TransactionData
{
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
};


//Block Data
class Block
{
private:
    int index;
    size_t blockHash;
    size_t previousHash;

    size_t generateHash()
    {
        hash<string> hash1;
        hash<size_t> hash2;
        hash<size_t> finalHash;
        string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

        return finalHash(hash1(toHash) + hash2(previousHash));
    };

public:
    //Constructor
    Block(int idx, TransactionData d, size_t prevHash)
    {
        index=idx;
        data=d;
        previousHash=prevHash;
        blockHash=generateHash();
    }

    //Get Original Hash
    size_t getHash()
    {
        return blockHash;
    }

    //Get previous hash
    size_t getPreviousHash()
    {
        return previousHash;
    }

    //Transaction Data
    TransactionData data;

    //validate hash
    bool isHashValid()
    {
        return generateHash()==blockHash;
    }
};



//Blockchain class
class BlockChain
{
private:
    Block createGenesisBlock()
    {
        time_t current;
        TransactionData d;
        d.amount=0;
        d.receiverKey="None";
        d.senderKey="None";
        d.timestamp=time(&current);

        hash<int> hash1;
        Block genesis(0, d, hash1(0));
        return genesis;
    }

public:
    //public chain
    vector<Block> chain;

    //Constructor
    BlockChain()
    {
        Block genesis = createGenesisBlock();
        chain.push_back((genesis));
    }

    //Public functions
    void addBlock(TransactionData d)
    {
        int index = (int)chain.size()-1;
        Block newBlock(index, d,getLatestBlock()->getHash());
    }

    bool isChainValid()
    {
        vector<Block>::iterator it;
        int chainLen=(int)chain.size();

        for(it=chain.begin();it!=chain.end();++it)
        {
            Block currentBlock = *it;
            if(!currentBlock.isHashValid())
            {
                return false;
            }

            if(chainLen>1)
            {
                Block previousHash = *(it-1);
                if(currentBlock.getPreviousHash()!=previousHash.getHash())
                {
                    return false;
                }
            }
        }
        return true;
    }

    //examplee onlyyyy
    Block *getLatestBlock()
    {
        return &chain.back();
    }
};

int main()
{
    BlockChain abc;

    //Data for first block
    TransactionData data1;
    time_t data1Time;
    data1.amount = 2;
    data1.receiverKey ="Joe";
    data1.senderKey = "DJ";
    data1.timestamp=time(&data1Time);

    abc.addBlock(data1);

    cout<<"Validity"<<endl
    <<abc.isChainValid();
}
