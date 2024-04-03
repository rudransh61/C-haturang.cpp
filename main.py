
import chess

class ChessAI:
    def __init__(self, depth):
        self.depth = depth

    def minimax(self, board, depth, alpha, beta, maximizing_player):
        if depth == 0 or board.is_game_over():
            return self.evaluate(board)

        if maximizing_player:
            max_eval = float('-inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.minimax(board, depth - 1, alpha, beta, False)
                board.pop()
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break  # Beta cut-off
            return max_eval
        else:
            min_eval = float('inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.minimax(board, depth - 1, alpha, beta, True)
                board.pop()
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break  # Alpha cut-off
            return min_eval

    def get_best_move(self, board):
        best_move = None
        max_eval = float('-inf')
        alpha = float('-inf')
        beta = float('inf')
        for move in board.legal_moves:
            board.push(move)
            eval = self.minimax(board, self.depth - 1, alpha, beta, False)
            board.pop()
            if eval > max_eval:
                max_eval = eval
                best_move = move
        return best_move

    def evaluate(self, board):
        # Basic evaluation function
        # Assign values to pieces and calculate score
        score = 0
        for square in chess.SQUARES:
            piece = board.piece_at(square)
            if piece:
                if piece.color == board.turn:
                    score += self.piece_value(piece)
                else:
                    score -= self.piece_value(piece)
        return score


    def piece_value(self, piece):
        if piece.piece_type == chess.PAWN:
            return 1
        elif piece.piece_type == chess.KNIGHT:
            return 3
        elif piece.piece_type == chess.BISHOP:
            return 3
        elif piece.piece_type == chess.ROOK:
            return 5
        elif piece.piece_type == chess.QUEEN:
            return 9
        elif piece.piece_type == chess.KING:
            return 1000  # This value is chosen arbitrarily for demonstration

def print_board(board):
    print(board)

def main():
    import chess

    # Initialize chess board
    board = chess.Board()

    # Initialize AI with depth
    ai = ChessAI(depth=3)

    while not board.is_game_over():
        print_board(board)
        if board.turn == chess.WHITE:
            user_move = input("Enter your move (in UCI format): ")
            try:
                move = chess.Move.from_uci(user_move)
                if move in board.legal_moves:
                    board.push(move)
                else:
                    print("Invalid move. Try again.")
            except ValueError:
                print("Invalid move format. Try again.")
        else:
            # AI's turn
            best_move = ai.get_best_move(board)
            board.push(best_move)
            print("AI's move:", best_move.uci())

    print("Game Over")
    print("Result:", board.result())

if __name__ == "__main__":
    main()
