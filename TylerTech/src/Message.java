public class Message {

    public Command command;
    public int firstArg = Integer.MIN_VALUE;
    public int secondArg = Integer.MIN_VALUE;

    @Override
    public String toString() {
        switch (command) {
            case Quit:
                return "Quit";
            case MakeMove:
                return "MakeMove";
            case MoveIs:
            case Opponent:
            case Start:
                return (command.toString() + " "
                        + (firstArg == Integer.MIN_VALUE ? " " : Integer.toString(firstArg)) + " "
                        + (secondArg == Integer.MIN_VALUE ? " " : Integer.toString(secondArg)))
                        .trim();
            default:
                return "";
        }
    }

    public static Message Start(int player) {
        return Create(Command.Start, player);
    }

    public static Message Quit() {
        return Create(Command.Quit);
    }

    public static Message Opponent(int board, int cell) {
        return Create(Command.Opponent, board, cell);
    }

    public static Message MoveIs(int board, int cell) {
        return Create(Command.MoveIs, board, cell);
    }

    public static Message MakeMove() {
        return Create(Command.MakeMove);
    }

    private static Message Create(Command c) {
        return Create(c, Integer.MIN_VALUE, Integer.MIN_VALUE);
    }

    private static Message Create(Command c, int firstArg) {
        return Create(c, firstArg, Integer.MIN_VALUE);
    }

    private static Message Create(Command c, int firstArg, int secondArg) {
        Message message = new Message();
        message.command = c;
        message.firstArg = firstArg;
        message.secondArg = secondArg;
        return message;
    }

    public static ParseResult tryParse(String s) {
        if (s == null || s.trim().length() == 0) {
            return ParseResult.INVALID;
        }

        String[] parts = s.split(" ");
        if (parts.length == 0) {
            return ParseResult.INVALID;
        }

        Command c = Command.getCommand(parts[0]);
        if (c.equals(Command.Invalid)) {
            return ParseResult.INVALID;
        }

        try {
            if (parts.length == 3) {
                int index1 = parts.length - 2;
                int index2 = parts.length - 1;

                return new ParseResult(true, c,
                        Integer.parseInt(parts[index1]),
                        Integer.parseInt(parts[index2]));
            }
            if (parts.length == 2) {
                int index1 = parts.length - 1;
                return new ParseResult(true, c,
                        Integer.parseInt(parts[index1]));
            }
            if (parts.length == 1) {
                return new ParseResult(true, c);
            }
            return ParseResult.INVALID;
        } catch (Exception e) {
            return ParseResult.INVALID;
        }
    }

    public static class ParseResult {

        public static final ParseResult INVALID = new ParseResult(false, null, Integer.MIN_VALUE, Integer.MIN_VALUE);

        public boolean didParse;
        public Command command;
        public int firstArg;
        public int secondArg;

        public ParseResult(boolean result, Command command) {
            this.didParse = result;
            this.command = command;
            this.firstArg = Integer.MIN_VALUE;
            this.secondArg = Integer.MIN_VALUE;
        }

        public ParseResult(boolean result, Command command, int firstArg) {
            this.didParse = result;
            this.command = command;
            this.firstArg = firstArg;
            this.secondArg = Integer.MIN_VALUE;
        }

        public ParseResult(boolean result, Command command, int firstArg, int secondArg) {
            this.didParse = result;
            this.command = command;
            this.firstArg = firstArg;
            this.secondArg = secondArg;
        }
    }

    public enum Command {

        Invalid, Quit, MakeMove, MoveIs, Opponent, Start;

        public static Command getCommand(String s) {
            if (s.equalsIgnoreCase("quit")) {
                return Quit;
            } else if (s.equalsIgnoreCase("makeMove")) {
                return MakeMove;
            } else if (s.equalsIgnoreCase("moveIs")) {
                return MoveIs;
            } else if (s.equalsIgnoreCase("Opponent")) {
                return Opponent;
            } else if (s.equalsIgnoreCase("start")) {
                return Start;
            } else {
                return Invalid;
            }
        }
    }
}
