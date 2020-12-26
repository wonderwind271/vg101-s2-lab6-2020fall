#include "lab6.h"
#include <vector>
#include <cmath>
//#include <iostream>
/***
 * For this LAB, you just need to change this file.
 * To finish Objective I, you should implement the functions in MyGame class
 * To finish Objective II, you should give interface to your MyBrain class and complete your judge function based on your MyGame class.
 */

using namespace std;

// Create Your Data Structure Here
int dist(Vector2<int> a, Vector2<int> b)
{
    return abs(a.x -b.x)+abs(a.y-b.y);
}
Vector2<int> nextloc(Vector2<int> loc, Direction d)
{
    Vector2<int> tempnext=loc;
    switch (d) //move A
    {
        case D_Left: tempnext.x--;break;
        case D_Up: tempnext.y--;break;
        case D_Down: tempnext.y++;break;
        case D_Right: tempnext.x++;break;
    }
    return tempnext;
}

int transmove(Move m)
{
    if(m==M_Straight)return 0;
    else if(m==M_Left)return -1;
    else return 1;
}


struct bullet
{
    Vector2<int> position;
    Direction d;
    int able=1;
    void move()//move only once
    {
        //Vector2<int> temp;
        if(able)
        {
            switch (d)
            {
                case D_Left: position.x--;break;
                case D_Up: position.y--;break;
                case D_Down: position.y++;break;
                case D_Right: position.x++;break;
            }
        }
    }
    void set(int a, int b)
    {
        position.x=a;
        position.y=b;
    }
    int isplace(int a,int b) const
    {
        if(position.x==a&&position.y==b&&able==1) return 1;
        else return 0;
    }
};



class MyGame : public Game {
    // Create Your Data Structure Here
    Vector2<int> A; //tank A position
    Vector2<int> B; //tank B position
    Direction adir;
    Direction bdir;
    int A_life;
    int B_life;
    vector<bullet*> allbullet;
    int bulletnum=0;
    int rround=0;
    /*
    * stack-like structure to store all the bullet
    * use allbullet.push_back(NULL); allbullet[bulletnum++]=new bullet; to add elm
    */

    int bound1=0;
    int bound2=19;
    //int crashstate;

public:
    /**
     * @param A_X The X position for P1
     * @param A_Y The Y position for P1
     * @param B_X The X position for P2
     * @param B_Y The Y position for P2
     * @param A_direction The direction for P1
     * @param B_direction The direction for P2
     * To know the definition of Direction type, you can look at `lab6.h`
     * D_Left (0) -> Towards negative X
     * D_Up (1) -> Towards negative y
     * D_Right (2) -> Towards positive X
     * D_Down (3) -> Towards positive Y
     */
    Vector2<int> getA() const
    {
        return A;
    }

    Vector2<int> getB() const
    {
        return B;
    }

    Direction getdirA() const
    {
        return adir;
    }

    Direction getdirB() const
    {
        return bdir;
    }

    int getbound1() const
    {
        return bound1;
    }

    int getbound2() const
    {
        return bound2;
    }
    vector<bullet*> getbullet() const
    {
        return allbullet;
    }

    int getAlife() const
    {
        return A_life;
    }

    int getBlife() const
    {
        return B_life;
    }

    int getround() const
    {
        return rround;
    }
    void initialize(int A_X, int A_Y, int B_X, int B_Y, Direction A_direction, Direction B_direction) override {
        // Initialize Your Game Here
        A.x=A_X;
        A.y=A_Y;
        B.x=B_X;
        B.y=B_Y;
        adir=A_direction;
        bdir=B_direction;
        A_life=5;
        B_life=5;
        //crashstate=0;
    }

    /**
     * @param tank The tank that is to move
     * Tank_A (0) -> P1
     * Tank_B (1) -> P2
     * @param move The move it wants to take
     * M_Straight (0) -> Go straightly
     * M_Left (1) -> Turn Left
     * M_Right (2) -> Turn Right
     */
    void move(Tank tank, Move move) override {
        // Record A Move And Update Your Game
        // 1. Move
        // 2. Shoot
        if(tank==Tank_A)
        {
            ++rround;
            int newdir;
            newdir=(adir+transmove(move))%4;
            if(newdir<0) newdir+=4;
            adir=Direction(newdir);//change direction
            switch (adir) //move A
            {
                case D_Left: A.x--;break;
                case D_Up: A.y--;break;
                case D_Down: A.y++;break;
                case D_Right: A.x++;break;
            }
            //cout<<"A:x="<<A.x<<"  "<<"y="<<A.y<<endl;
            if(rround%3 == 1)//shoot
            {
                allbullet.push_back(new bullet);
                //allbullet[bulletnum]=new bullet;
                int tempx=0,tempy=0;
                switch (adir) //move vector
                {
                    case D_Left: tempx=-1;break;
                    case D_Up: tempy=-1;break;
                    case D_Down: tempy=1;break;
                    case D_Right: tempx=1;break;
                }
                allbullet[bulletnum]->set(A.x+tempx,A.y+tempy);
                //cout<<"set bullet in "<<A.x+tempx<<","<<A.y+tempy<<endl;
                allbullet[bulletnum]->d=adir;
                ++bulletnum;
            }

        }
        else
        {


            int newdir;
            newdir=(bdir+transmove(move))%4;
            if(newdir<0) newdir+=4;
            bdir=Direction(newdir);//change direction
            switch (bdir) //move B
            {
                case D_Left: B.x--;break;
                case D_Up: B.y--;break;
                case D_Down: B.y++;break;
                case D_Right: B.x++;break;
            }
            //cout<<"B:x="<<B.x<<"  "<<"y="<<B.y<<endl;
            if(rround%3 == 1)//shoot
            {
                //allbullet[bulletnum]=new bullet;
                allbullet.push_back(new bullet);
                int tempx=0,tempy=0;
                switch (bdir) //move vector
                {
                    case D_Left: tempx=-1;break;
                    case D_Up: tempy=-1;break;
                    case D_Down: tempy=1;break;
                    case D_Right: tempx=1;break;
                }
                allbullet[bulletnum]->set(B.x+tempx,B.y+tempy);
                //cout<<"set bullet in "<<B.x+tempx<<","<<B.y+tempy<<endl;
                allbullet[bulletnum]->d=bdir;
                ++bulletnum;
            }
        }



    }




    /**
     * Calculate the result at the end of the turn. It will be called after two tanks makes their move.
     * @return
     * T_Cont (0) -> Game continues
     * T_A_Win (1) -> P1 Wins
     * T_B_Win (2) -> P2 Wins
     * T_Draw (3) -> Draw
     */
    Turn turn() override {
        // Make Your Turn Here
        // 0. Tank Crash
        //cout<<"round="<<round<<endl;

        if(A==B)return T_Draw;//A=B means B go to A's place and crashstate=1 means A goto B's place

        // 1. Move Bullets and deduct lifes
        // 2. Track 3 points

        for(int i=0;i<bulletnum;i++)// check 1/3
        {
            if(A==allbullet[i]->position&&allbullet[i]->able)
            {A_life-=2;allbullet[i]->able=0;
            //cout<<"A-1\n";
            }

            if(B==allbullet[i]->position&&allbullet[i]->able) {B_life-=2;allbullet[i]->able=0;
            //cout<<"B-1\n";
            }
        }


        for(int i=0;i<bulletnum;i++)//move the bullet 1/2
        {
            allbullet[i]->move();
        }

        for(int i=0;i<bulletnum;i++)// check 2/3
        {
            if(A==allbullet[i]->position&&allbullet[i]->able) {A_life-=2;allbullet[i]->able=0;
            //cout<<"A-1\n";
            }
            if(B==allbullet[i]->position&&allbullet[i]->able) {B_life-=2;allbullet[i]->able=0;
            //cout<<"B-1\n";
            }
        }

        for(int i=0;i<bulletnum;i++)//move the bullet 2/2
        {
            allbullet[i]->move();
        }

        for(int i=0;i<bulletnum;i++)// check 3/3
        {
            if(A==allbullet[i]->position&&allbullet[i]->able) {A_life-=2;allbullet[i]->able=0;
            //cout<<"A-1\n";
            }
            if(B==allbullet[i]->position&&allbullet[i]->able) {B_life-=2;allbullet[i]->able=0;
            //cout<<"B-1\n";
            }
        }

        // 2. Out of Boundary
        if(rround%16==0)//shrink
        {
            ++bound1;
            --bound2;
        }
        if(A.x<bound1||A.x>bound2||A.y<bound1||A.y>bound2)
        {
            --A_life; //judge A
            //cout<<"A out!\n";
        }
        if(B.x<bound1||B.x>bound2||B.y<bound1||B.y>bound2)
        {
            --B_life; //judge B
            //cout<<"B out!\n";
        }
        // 3. Win or Lose
        if(A_life<=0&&B_life<=0) return T_Draw;
        else if(A_life<=0&&B_life>0) return T_B_Win;
        else if(B_life<=0&&A_life>0) return T_A_Win;
        else
            return T_Cont;
    }

    /**
     * Draw the battlefield
     * @return
     */
    string draw() const
    {
        //cout<<"A="<<A_life<<endl;
        //cout<<"B="<<B_life<<endl;
        string field(30*31,' ');//the batterfield
        char strfield[31][30]={0};
        for(int i=0;i<30;i++)
        {
            for(int j=0;j<30;j++)
            {
                strfield[i][j]=' ';
            }
        }
        for(int j=0;j<30;j++)strfield[30][j]='\n';
        //main field is from 5 to 24, where 0-4; 25-29 are outside
        //x'=x+5, x is the "x" in A.x or B.x
        //[][30]store '\n'
        for(int i=0;i<30;i++)
        {
            for(int j=0;j<30;j++)
            {
                int tempx=i-5, tempy=j-5;
                if((tempx==bound1||tempx==bound2||tempy==bound1||tempy==bound2)&&tempx>=bound1&&tempx<=bound2&&tempy>=bound1&&tempy<=bound2) strfield[i][j]='*';//draw boundary

                for(int k=0;k<bulletnum;k++)
                {
                    if(allbullet[k]->isplace(tempx,tempy)&&allbullet[k]->able==1)
                        strfield[i][j]='>';
                }

                if(tempx==A.x&&tempy==A.y) strfield[i][j]='A';
                if(tempx==B.x&&tempy==B.y) strfield[i][j]='B'; //draw tank A and B


            }
        }
        //move strfield into field

        int tempk=0;
        for(int j=0;j<30;j++)
        {
            for(int i=0;i<31;i++)
            {
                field[tempk]=strfield[i][j];
                ++tempk;
            }
        }

        return field;
    }
    ~MyGame()
    {
        for(int i=0;i<bulletnum;i++) delete allbullet[i];
    }
};

class MyBrain : public Brain {
    // Create Your Status Variables Here
    Vector2<int> placeA;
    Vector2<int> placeB;
    Direction adir;
    Direction bdir;
    Vector2<int> nextA;
    Vector2<int> nextB;
    int bound1,bound2;
    int nbound1,nbound2;
    const MyGame* game = nullptr;
    vector<bullet*> gbullet; //get all bullet
    int Alife, Blife;
    int length; //length of A and B
    int rround;
    int statejudge[4]; //-2 for out, -1 for hit by bullet, 1 for approach, 0 for normal, 2 for crash-danger, 3 for track

public:
    void initialize() override {
        // Initialize Your AI here
        //rround=1;




        game = dynamic_cast<MyGame*>(getMyGame()); // This will give you a MyGame pointer from the Game pointer returned by getMyGame() So you can access the variable before it's declared.
    }



    Move judge() override {
        // Move Your Move Here
        for(int i=0;i<4;i++) statejudge[i]=0;
        rround=game->getround();
        //cout<<rround<<endl;
        gbullet=game->getbullet();
        placeA=game->getA();
        //cout<<"A:"<<placeA.x<<" "<<placeA.y<<endl;
        placeB=game->getB();
        //cout<<"B:"<<placeB.x<<" "<<placeB.y<<endl;
        length=dist(placeA,placeB);
        adir=game->getdirA();
        bdir=game->getdirB();
        bound1=game->getbound1();
        bound2=game->getbound2();
        if(rround%16==15)
        {
            nbound1=bound1+1;
            nbound2=bound2-1;
        }
        else
        {
            nbound1=bound1;
            nbound2=bound2;
        }
        Alife=game->getAlife();
        Blife=game->getBlife();
        //cout<<"Alife:"<<Alife<<"\nBlife:"<<Blife<<endl;
        nextA=placeA;


        switch (adir) //simumove A
        {
            case D_Left: nextA.x--;break;
            case D_Up: nextA.y--;break;
            case D_Down: nextA.y++;break;
            case D_Right: nextA.x++;break;
        }
        nextB=placeB;
        switch (bdir) //simumove B
        {
            case D_Left: nextB.x--;break;
            case D_Up: nextB.y--;break;
            case D_Down: nextB.y++;break;
            case D_Right: nextB.x++;break;
        }

        gbullet=game->getbullet();
        //cout<<nextA.x<<" "<<nextA.y<<endl;
        //initialize complete

        for(int i=0;i<3;i++)// evaluate for 3 kinds of move
        {
            Move temp; //evaulated move, from 0 to 2
            int atemp;
            Direction tempdir;//evaluated direction
            Vector2<int> nextplace;//evaluated a's next place
            temp=Move(i);
            atemp=adir+transmove(temp);
            if(atemp<0)atemp+=4;
            tempdir=Direction(atemp);
            nextplace=nextloc(placeA,tempdir);
            if(nextplace.x<nbound1||nextplace.y<nbound1||nextplace.x>nbound2||nextplace.y>nbound2)
                statejudge[i]=-2; //-2 for out

            else //judge bullet
            {
                vector<bullet>simubullet(gbullet.size());
                for(int j=0;j<(int)gbullet.size();j++) //get a copy
                {
                    simubullet[j]= *(gbullet[j]);
                }
                for(int j=0;j<(int)simubullet.size();j++)//judge 1/3
                {
                    if(nextplace==simubullet[j].position&&simubullet[j].able)
                        statejudge[i]=-1;//-1 for hit by bullet
                }
                for(int j=0;j<(int)simubullet.size();j++)//move 1/2
                {
                    simubullet[j].move();
                }

                for(int j=0;j<(int)simubullet.size();j++)//judge 2/3
                {
                    if(nextplace==simubullet[j].position&&simubullet[j].able)
                        statejudge[i]=-1;//-1 for hit by bullet
                }

                for(int j=0;j<(int)simubullet.size();j++)//move 1/2
                {
                    simubullet[j].move();
                }

                for(int j=0;j<(int)simubullet.size();j++)//judge 3/3
                {
                    if(nextplace==simubullet[j].position&&simubullet[j].able)
                        statejudge[i]=-1;//-1 for hit by bullet
                }
                //for round before shoot, dangerous to stand in front of oppo within T+2 to T+4
                if(rround%3==0&&statejudge[i]>=0)
                {
                    //use placeB and bdir, suppose B keep it's direction
                    Vector2<int> t[4];


                    t[0]=nextloc(placeB,bdir);
                    //t[0] is nextplace of b
                    for(int j=0;j<3;j++)
                    {
                        t[j+1]=nextloc(t[j],bdir);
                    }
                    //t[1] to t[3] are dangerous points
                    if(nextplace==t[1]||nextplace==t[2]||nextplace==t[3])
                    {
                        statejudge[i]=-1;
                    }
                    //..

                    t[0]=nextloc(placeB,Direction((bdir+1)%4));
                    //t[0] is nextplace of b
                    for(int j=0;j<3;j++)
                    {
                        t[j+1]=nextloc(t[j],Direction((bdir+1)%4));
                    }
                    //t[1] to t[3] are dangerous points
                    if(nextplace==t[1]||nextplace==t[2]||nextplace==t[3])
                    {
                        statejudge[i]=-1;
                    }
                    //..

                    t[0]=nextloc(placeB,Direction((bdir+3)%4));
                    //t[0] is nextplace of b
                    for(int j=0;j<3;j++)
                    {
                        t[j+1]=nextloc(t[j],Direction((bdir+3)%4));
                    }
                    //t[1] to t[3] are dangerous points
                    if(nextplace==t[1]||nextplace==t[2]||nextplace==t[3])
                    {
                        statejudge[i]=-1;
                    }

                }

            }
            if(statejudge[i]>=0)//seek approach
            {
                if(dist(placeB,nextplace)<length) //find approach
                {
                    statejudge[i] = (length == 2) ? 2 : 1; // 2 for possible to crash, 1 for simple approach
                }
            }
            if(statejudge[i]==2)//sometimes cannot crash for the direction
            {
                if(adir==bdir) //dir's difference means always probable to crash, so only consider same dir
                {
                    if(placeA==nextloc(nextloc(placeB,adir),adir)||placeB==nextloc(nextloc(placeA,adir),adir))
                        statejudge[i]=3;//track, that's good because oppo may be hit.
                }
            }
          /*  if(statejudge[i]==1&&adir!=bdir) //hit other purposefully
            {
                if((nextplace.x==nextB.x||nextplace.y==nextB.y)&&(placeA.x==nextB.x||placeA.y==nextB.y))
                {
                    //cout<<"here\n";
                    statejudge[i]=3;//approach and go in a line
                    //return Move(i);
                }
            }*/

        }


        if(rround<=14)
        {
            if(rround%2==0) return M_Right;
            else return M_Left;
        }
        else //attempt to approach
        {
            for(int i=0;i<3;i++)
            {
                if (statejudge[i] == 3) return Move(i);
            }

            for(int i=0;i<3;i++)
            {
                //if(statejudge[i]==3) return Move(i);
                if(statejudge[i]>0)
                {
                    if(statejudge[i]==2&&(Alife<Blife || (Alife==Blife&&rround<=120)))
                    {
                        statejudge[i]=-1;
                        continue;
                    }
                    else
                        return Move(i);
                }

            }

            if(statejudge[1]>=0)
            {
                return M_Left;
            }
            else if(statejudge[0]>=0)
            {
                return M_Straight;
            }
            else if(statejudge[2]>=0)
            {
                return M_Right;
            }
            else
            {
                for(int i=0;i<=2;i++)
                {
                    if(statejudge[i]!=-2) return Move(i);
                }
                return M_Right;
            }

        }


        /*if(nextA.x<bound1||nextA.x>bound2||nextA.y<bound1||nextA.y>bound2)
            return M_Right;
        else
            return M_Straight;*/




        /*    if((placeA.x==bound1||placeA.x==bound2||placeA.y==bound1||placeA.y==bound2)&&outrisk==1)
            return M_Straight;
            else {
                outrisk=0;
                return  M_Left;*/

    }
};

static MyGame game;
static MyBrain brain;

Game* getMyGame() {
    return &game;
}

Brain* getMyBrain() {
    return &brain;
}