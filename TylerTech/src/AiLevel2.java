import java.util.ArrayList;
import java.util.Objects;
import java.util.Random;
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

public class AiLevel2 {

    public static int _boardLength;
    public static int[][] _currentBoard;
    public static int _currentPlayer;
    public static int _opposingNumber;
    public static int _playerNumber;

    /*
    public GridPane setupGUI(Stage stage) {
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setGridLinesVisible(true);
        for (int j = 0; j < _boardLength; j++) {
            for (int i = 0; i < _boardLength; i++) {
                final Button square = new Button("   ");
                square.textProperty().bind(_currentBoard[i][j]);
                square.textProperty().addListener((observable, oldValue, newValue) -> {
                    square.setDisable(true);
                });
                final int row = i;
                final int col = j;
                square.setOnAction(e -> {
                    _currentBoard[row][col].setValue(Integer.toString(_opposingNumber));
                    MakeMove(_opposingNumber, row, col);
                });
                grid.add(square, j, i);
            }
        }
        return grid;
    }
    */

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
                            if (currentMessage.secondArg == Integer.MIN_VALUE)
                                Setup((int) currentMessage.firstArg, 3);
                            else
                                Setup((int) currentMessage.firstArg, (int) currentMessage.secondArg);
                            /*
                            GridPane grid = setupGUI(stage);
                            Scene scene = new Scene(grid);
                            stage.setScene(scene);
                            stage.setTitle("Tic-Tac-Toe");
                            stage.show();
                            */
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

    public static void Setup(int playerNumber, int boardLength) {
        if (!(playerNumber == 1 || playerNumber == 2)) {
            throw new RuntimeException("Player number must be 1 or 2");
        }
        _playerNumber = playerNumber;
        _opposingNumber = _playerNumber == 1 ? 2 : 1;
        _boardLength = boardLength;
        _currentBoard = new int[_boardLength][_boardLength];
        for (int i = 0; i < _boardLength; i++)
            for (int j = 0; j < _boardLength; j++) {
                //_currentBoard[i][j] = new SimpleStringProperty();
                _currentBoard[i][j] = 0;
            }
    }

    private static Tuple<Integer, Integer> FindNextMove(int player) {
        int maxScore = Integer.MIN_VALUE;
        int opponent = player == 1 ? 2 : 1;
        ArrayList<Tuple<Integer, Integer>> moves = genMoves(_currentBoard);
        ArrayList<Tuple<Integer, Integer>> specialMoves = new ArrayList<>();
        //Diagonal
        for (int i = 0; i < _boardLength; i++) {
            if (moves.contains(new Tuple<>(i, i)))
                specialMoves.add(new Tuple<>(i, i));
        }
        for (int i = 0; i < _boardLength; i++) {
            if (_currentBoard[i][i] == opponent) {
                moves.removeAll(specialMoves);
            }
            if (i == _boardLength - 1)
                return specialMoves.get(new Random().nextInt(specialMoves.size()));
        }
        //Diagonal
        for (int i = 0; i < _boardLength; i++) {
            if (moves.contains(new Tuple<>(i, _boardLength - 1 - i)))
                specialMoves.add(new Tuple<>(i, _boardLength - 1 - i));
        }
        for (int i = 0; i < _boardLength; i++) {
            if (_currentBoard[i][_boardLength - 1 - i] == opponent) {
                moves.removeAll(specialMoves);
            }
            if (i == _boardLength - 1)
                return specialMoves.get(new Random().nextInt(specialMoves.size()));
        }
        return moves.get(new Random().nextInt(moves.size()));
    }
    
    private static ArrayList<Tuple<Integer, Integer>> genMoves(int[][] state) {
        ArrayList<Tuple<Integer, Integer>> moves = new ArrayList<Tuple<Integer, Integer>>();
        for (int i = 0; i < _boardLength; i++) {
            for (int j = 0; j < _boardLength; j++) {
                //if (state[i][j].getValue().equals("   ")) {
                if (state[i][j] == 0) {
                    moves.add(new Tuple<Integer, Integer>(i, j));
                }
            }
        }
        return moves;
    }

    public static void MakeMove(int player, int row, int col) {
        //_currentBoard[row][col].setValue(player == 1 ? "X" : "O");
        _currentBoard[row][col] = player;
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
        
        @Override
        public boolean equals(Object other) {
            if (other == null) return false;
            if (other instanceof Tuple) {
                return a.equals(((Tuple) other).a) && b.equals(((Tuple) other).b);
            }
            return false;
        }

        @Override
        public int hashCode() {
            int hash = 5;
            hash = 53 * hash + Objects.hashCode(this.a);
            hash = 53 * hash + Objects.hashCode(this.b);
            return hash;
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
        int[][] state = new int[_boardLength][_boardLength];
        for (int i = 0; i < _boardLength; i++) {
            for (int j = 0; j < _boardLength; j++) {
                if (i == row && j == col) {
                    state[i][j] = player;
                } else {
                    state[i][j] = oldState[i][j];
                }
            }
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
            return _boardLength * _boardLength + 1 - spacesFilled(state);
        } else if (spacesFilled(state) == _boardLength * _boardLength) {
            //draw state
            return 0;
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
            return maxScore;
        }
    }

    private static boolean isWinningState(int[][] state, int player, Tuple<Integer, Integer> move) {
        int row = move.a;
        int col = move.b;

        //Vertical line
        for (int i = 0; i < _boardLength; i++) {
            if (state[i][col] != player) {
                break;
            }
            if (i == _boardLength - 1)
                return true;
        }
        //Horizontal line
        for (int j = 0; j < _boardLength; j++) {
            if (state[row][j] != player) {
                break;
            }
            if (j == _boardLength - 1)
                return true;
        }
        //Diagonal
        if (row == col) {
            for (int i = 0; i < _boardLength; i++) {
                if (state[i][i] != player) {
                    break;
                }
                if (i == _boardLength - 1)
                    return true;
            }
        }
        //Diagonal
        if (row + col == _boardLength - 1) {
            for (int i = 0; i < _boardLength; i++) {
                if (state[i][_boardLength - 1 - i] != player) {
                    break;
                }
                if (i == _boardLength - 1)
                    return true;
            }
        }
        return false;
    }

    private static int spacesFilled(int[][] state) {
        int count = 0;
        for (int i = 0; i < _boardLength; i++) {
            for (int j = 0; j < _boardLength; j++) {
                if (state[i][j] != 0) {
                    count++;
                }
            }
        }
        return count;
    }
}
