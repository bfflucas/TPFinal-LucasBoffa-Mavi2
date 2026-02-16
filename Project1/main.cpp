#include "Start.h"
#include "Game.h"

int main(int argc, char* args[])
{
    Start _start;
    _start.Loop();
    Game partida1({ 1200,900 }, "Ragdol simple");

    return 0;
   
}


