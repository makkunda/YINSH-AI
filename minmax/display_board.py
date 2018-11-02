import sys
sys.path.append("/home/vision/Downloads/AI/YINSH-AI/starter_code/")
import game

if __name__=="__main__":
    myGame = game.Game(5, 'GUI')
    # for line in sys.stdin.readlines():
    #     print "Executing - "+line
    #     myGame.execute_sequence(line.strip().split())
    while 1:
        line = raw_input()
        print "Executing - "+line
        success = myGame.execute_sequence(line.strip().split())
        if not success:
            print 'Wrong Move!'
            break
        if myGame.check_won():
            print "Game Ended! " + "Player " + str(myGame.get_current_player()^1 + 1)+ " Won"
            break

    print "Exiting"