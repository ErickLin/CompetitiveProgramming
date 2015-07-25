import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
/*
import javafx.application.Application;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
*/

public class AiLevel3 {

    public static int[][] _currentBoard;
    public static int _currentPlayer;
    public static int _playerNumber;
    public static int _opposingNumber;
    public static Tuple<Integer, Integer> _lastOpponentMove;
    public static HashMap<Integer, Integer> _scoresHash;

    public static void main(String[] args) {
        try {
            //new PrintStream(System.out, true, "IBM437");
            Message.ParseResult currentMessage;
            Scanner input = new Scanner(System.in);
            do {
                String nextLine = input.nextLine();
                currentMessage = Message.tryParse(nextLine);

                if (currentMessage.didParse) {
                    switch (currentMessage.command) {
                        case Start:
                            DebugAssert(currentMessage.firstArg != Integer.MIN_VALUE, "Setup requires a player number.");
                            Setup((int) currentMessage.firstArg);
                            break;
                        case Opponent:
                            DebugAssert(currentMessage.firstArg != Integer.MIN_VALUE, "Opponent move requires a row number.");
                            DebugAssert(currentMessage.secondArg != Integer.MIN_VALUE, "Opponent move requires a column number.");
                            MakeMove(_opposingNumber, currentMessage.firstArg, currentMessage.secondArg);
                            break;
                        case MakeMove:
                            Tuple<Integer, Integer> move = FindNextMove(_playerNumber);
                            MakeMove(_playerNumber, move.a, move.b);
                            Message myMove = Message.MoveIs(move.a, move.b);
                            System.out.println(myMove.toString());
                            System.out.flush();
                            break;
                        case Quit:
                        default:
                            break;
                    }
                }

            } while (currentMessage.didParse && !currentMessage.command.equals(Message.Command.Quit));
            input.close();
            System.exit(0);
        } catch (Exception e) {
            System.err.println(e);
            System.exit(0);
        }
    }

    public static void Setup(int playerNumber) {
        if (!(playerNumber == 1 || playerNumber == 2)) {
            throw new RuntimeException("Player number must be 1 or 2");
        }
        _playerNumber = playerNumber;
        _opposingNumber = _playerNumber == 1 ? 2 : 1;
        _currentBoard = new int[9][9];
        //Causes AI to always start in top-left corner if it goes first
        _lastOpponentMove = new Tuple<>(0, 0);
        _scoresHash = new HashMap<Integer, Integer>();
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                _currentBoard[i][j] = 0;
            }
    }

    private static Tuple<Integer, Integer> FindNextMove(int player) {
        int maxScore = Integer.MIN_VALUE;
        Tuple<Integer, Integer> nextMove = new Tuple(0, 0);
        int[][] smallBoard = new int[3][3];
        int startRow = (_lastOpponentMove.a % 3) * 3;
        int startCol = (_lastOpponentMove.b % 3) * 3;
        ArrayList<Tuple<Integer, Integer>> moves = genMoves(smallBoard);
        for (Tuple<Integer, Integer> move : moves) {
            int score = score(smallBoard, player, move);
            if (score > maxScore) {
                maxScore = score;
                nextMove = move;
            }
        }
        return new Tuple<>(startRow + nextMove.a, startCol + nextMove.b);
    }
    
    private static ArrayList<Tuple<Integer, Integer>> genMoves(int[][] state) {
        ArrayList<Tuple<Integer, Integer>> moves = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == 0) {
                    moves.add(new Tuple<>(i, j));
                }
            }
        }
        return moves;
    }

    public static void MakeMove(int player, int row, int col) {
        _currentBoard[row][col] = player;
        if (player == _opposingNumber) {
            _lastOpponentMove = new Tuple<>(row, col);
        }
    }

    public static void DebugAssert(boolean condition, String error) {
        if (!condition) {
            throw new RuntimeException(error);
        }
    }

    private static class Tuple<A, B> {

        A a;
        B b;

        Tuple(A a, B b) {
            this.a = a;
            this.b = b;
        }
        
        @Override
        public String toString() {
            return a.toString() + ", " + b.toString();
        }
    }

    /**
     * Returns the "score" used to rank each potential move
     * @param player the player number
     * @param oldState the placement of X's and O's on the hypothetical board
     * @param move the potential move to be made
     * @return a number - the higher it is, the closer to optimal the move
     */
    private static int score(int[][] oldState, int player, Tuple<Integer, Integer> move) {
        int row = move.a;
        int col = move.b;
        int[][] state = new int[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == row && j == col) {
                    state[i][j] = player;
                } else {
                    state[i][j] = oldState[i][j];
                }
            }
        }
        int stateHash = hash(state);
        if (_scoresHash.containsKey(stateHash)) {
            //System.out.println("Hash: " + stateHash
            //        + " Score: " + _scoresHash.get(stateHash));
            return _scoresHash.get(stateHash);
        }
        int opponent = (player == 1) ? 2 : 1;
        if (isWinningState(state, player, move)) {
            /*
            for (int i = 0; i < _boardLength; i++) {
                for (int j = 0; j < _boardLength; j++) {
                    System.out.print(state[i][j] + " ");
                }
                System.out.println();
            }
            System.out.println();
            */
            int ret = 3 * 3 + 1 - spacesFilled(state);
            _scoresHash.put(hash(state), ret);
            return ret;
        } else if (spacesFilled(state) == 3 * 3) {
            //draw state
            int ret = 0;
            _scoresHash.put(hash(state), ret);
            return ret;
        } else {
            //opponent's turn
            int maxScore = Integer.MIN_VALUE;
            ArrayList<Tuple<Integer, Integer>> opponentMoves = genMoves(state);
            for (Tuple<Integer, Integer> opponentMove : opponentMoves) {
                int score = -score(state, opponent, opponentMove);
                if (score > maxScore) {
                    maxScore = score;
                }
            }
            int ret = maxScore;
            _scoresHash.put(hash(state), ret);
            return ret;
        }
    }

    //returns unique value for a two-dimensional board
    private static int hash(int[][] state) {
        int hash = 0;
        int count = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                hash += (int) (Math.pow(3, count)) * state[i][j];
                count++;
            }
        return hash;
    }

    private static boolean isWinningState(int[][] state, int player, Tuple<Integer, Integer> move) {
        int row = move.a;
        int col = move.b;

        //Vertical line
        for (int i = 0; i < 3; i++) {
            if (state[i][col] != player) {
                break;
            }
            if (i == 2)
                return true;
        }
        //Horizontal line
        for (int j = 0; j < 3; j++) {
            if (state[row][j] != player) {
                break;
            }
            if (j == 2)
                return true;
        }
        //Diagonal
        if (row == col) {
            for (int i = 0; i < 3; i++) {
                if (state[i][i] != player) {
                    break;
                }
                if (i == 2)
                    return true;
            }
        }
        //Diagonal
        if (row + col == 2) {
            for (int i = 0; i < 3; i++) {
                if (state[i][2 - i] != player) {
                    break;
                }
                if (i == 2)
                    return true;
            }
        }
        return false;
    }

    private static int spacesFilled(int[][] state) {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] != 0) {
                    count++;
                }
            }
        }
        return count;
    }
}
