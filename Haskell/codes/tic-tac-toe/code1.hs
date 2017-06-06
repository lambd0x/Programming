import Data.List
import Data.List.Split
import Control.Monad

------------------------------
------- Single Player --------
------------------------------

-------------------------------
-- Print the game
mostraTabuleiro str =
 "   |   |   \n" ++ " " ++ (str !! 0 :[]) ++ " | " ++ (str !! 1 :[]) ++ " | " ++ (str !! 2 :[])  ++ " \n" ++ 
 "   |   |   \n" ++ 
 "---+---+---\n" ++
 "   |   |   \n" ++ " " ++ (str !! 3 :[]) ++ " | " ++ (str !! 4 :[]) ++ " | " ++ (str !! 5 :[])  ++ " \n" ++
 "   |   |   \n" ++
 "---+---+---\n" ++
 "   |   |   \n" ++ " " ++ (str !! 6 :[]) ++ " | " ++ (str !! 7 :[]) ++ " | " ++ (str !! 8 :[])  ++ " \n" ++
 "   |   |   \n"

-------------------------------
--Verifies whether the number is between the boundaries such as [0 <= c <= 9]
eNumero c = filter (\x->x==c) ['0'..'9'] /= []

-------------------------------
--Verifies whether the play is valid
-- Dependências: eNumero
jogadaValida tabuleiro p
 | p < 0 || p >= 9 = False          -- ok if within boundaries
 | eNumero(tabuleiro !! p) = True   -- ok if player's moviment doesn't return a letter (causing a []) 
 | otherwise = False                -- says if the position is already taken
  
-------------------------------
--Verifies the possible gaming options and return it as a list
-- Dependências: vitoria, jogadaValida
jogadaPossivel tabuleiro
 | (vitoria tabuleiro) /= ' ' = []
 | otherwise = [y | y <- [0..8], (jogadaValida tabuleiro y)]
  
-------------------------------
--Insert the moviment in the table
-- Dependências: ins
ins (p:tabuleiro) jogChar pos
 | pos > 0 = p:[] ++ (ins tabuleiro jogChar (pos - 1))
 | otherwise = jogChar:[] ++ tabuleiro
 
-------------------------------
--Tells who has won 
-- Dependências: vitoria
jogadorVencedor tabuleiro jogador
 | (vitoria tabuleiro) == ' '   = 0
 | (vitoria tabuleiro) == jogador = 1
 | otherwise = -1
  
-------------------------------
--Verifies the equality of the tuples 
-- Dependências: none
cmpTuplas fn (m0, s0) (m1, s1)
 | fn s0 s1 = (m0, s0)
 | otherwise = (m1, s1)
 
-------------------------------
--Select the cpu's moviment 
-- Dependências: cmpTuplas
selecionaMove fn (mv:moves) = foldr (cmpTuplas fn) mv moves

-------------------------------
--Mini CPU's evaluation function 
-- Dependências: jogadaPossivel, jogadorVencedor, ins, avaliarTabuleiroMax
avaliarTabuleiroMini tabuleiro
 | length (jogadaPossivel tabuleiro) == 0 = jogadorVencedor tabuleiro 'O'
 | otherwise = foldr max (head placar) (tail placar)
 where
  tabuleiro' = map (ins tabuleiro 'O') (jogadaPossivel tabuleiro)
  placar = map avaliarTabuleiroMax tabuleiro'

------------------------------
--Max CPU's evaluation function
-- Dependências: jogadaPossivel, jogadorVencedor, ins, avaliarTabuleiroMini
avaliarTabuleiroMax tabuleiro
 | length (jogadaPossivel tabuleiro) == 0    = jogadorVencedor tabuleiro 'O'
 | otherwise = foldr min (head placar) (tail placar)
 where
  tabuleiro' = map (ins tabuleiro 'X') (jogadaPossivel tabuleiro)
  placar = map avaliarTabuleiroMini tabuleiro'
 
------------------------------
--Define a score for each position to be evaluated by the CPU
-- Dependências: jogadaPossivel, ins, avaliarTabuleiroMax
pontuacaoPosicoes tabuleiro = zip (jogadaPossivel tabuleiro) placar
 where
  tabuleiro' = map (ins tabuleiro 'O') (jogadaPossivel tabuleiro)
  placar = map avaliarTabuleiroMax tabuleiro'

------------------------------
--Define the highest score from the set of positions
pontuacaoPosicoesMax (m0, s0) (m1, s1)
 | s0 > s1 = (m0, s0)
 | otherwise = (m1, s1)
  
------------------------------
--Chooses the best play for the CPU. Action takes the score of the positions in account
-- Dependências: pontuacaoPosicoesMax, pontuacaoPosicoes
melhorJogada tabuleiro = ins
 where
  placar = pontuacaoPosicoes tabuleiro
  (ins, a) = foldr pontuacaoPosicoesMax (head placar) (tail placar)
  
------------------------------
--Current play of P1 in Single Player 
-- Dependências: jogadaValida, ins
jogadaJogador tabuleiro pos
 | not (jogadaValida tabuleiro pos) = (False, tabuleiro) -- Se falso retorna-o junto ao tabuleiro inalterado
 | otherwise = (True, (ins tabuleiro 'X' pos))           -- Se verdade retorna-o junto ao tabuleiro atualizado

------------------------------
--Current play of P2 in Multiplayer 
-- Dependências: jogadaValida, ins
jogadaJogador2 tabuleiro pos
 | not (jogadaValida tabuleiro pos) = (False, tabuleiro) -- Se falso retorna-o junto ao tabuleiro inalterado
 | otherwise = (True, (ins tabuleiro 'O' pos))           -- Se verdade retorna-o junto ao tabuleiro atualizado
 
------------------------------
--Verifies all the victory conditions
vitoria t
 -- Testes horizontais
 | (t !! 0) /= ' ' && ((t !! 0) == (t !! 1) && (t !! 0) == (t !! 2)) = t !! 0
 | (t !! 3) /= ' ' && ((t !! 3) == (t !! 4) && (t !! 3) == (t !! 5)) = t !! 3
 | (t !! 6) /= ' ' && ((t !! 6) == (t !! 7) && (t !! 6) == (t !! 8)) = t !! 6
 -- Testes verticais
 | (t !! 0) /= ' ' && ((t !! 0) == (t !! 3) && (t !! 0) == (t !! 6)) = t !! 0
 | (t !! 1) /= ' ' && ((t !! 1) == (t !! 4) && (t !! 1) == (t !! 7)) = t !! 1
 | (t !! 2) /= ' ' && ((t !! 2) == (t !! 5) && (t !! 2) == (t !! 8)) = t !! 2
 -- Testes diagonais
 | (t !! 0) /= ' ' && ((t !! 0) == (t !! 4) && (t !! 0) == (t !! 8)) = t !! 0
 | (t !! 2) /= ' ' && ((t !! 2) == (t !! 4) && (t !! 2) == (t !! 6)) = t !! 2
 -- Velha      
 | otherwise = ' '

------------------------------
--Main routine of Single Player mode
-- Dependências: mostraTabuleiro, vitoria, jogadaPossivel, jogadaJogador, melhorJogada
jogarSingle tabuleiro = do
    --apresenta o tabuleiro
    putStrLn (mostraTabuleiro tabuleiro)
    --verifica se há vencedor
    if((vitoria tabuleiro) /= ' ') then do
      --Se houver vencedor o apresenta junto ao seu símbolo (X ou O)
      putStrLn("Vencedor " ++ (show (vitoria tabuleiro)));
    else do
        --atualiza a string de jogadas possíveis da partida
        putStrLn(show (jogadaPossivel tabuleiro)) 
        putStrLn("Qual deseja jogar? ")
        pos <- getLine
        --avalia a jogada do jogador e atualiza o tabuleiro se necessário
        let (valido, b) = (jogadaJogador tabuleiro (read pos))
        --se tiver havido modificação será avaliado um True
        if (valido) then do
             --se não houver jogadas possíveis
             if(length (jogadaPossivel tabuleiro) == 1) then do
                 putStrLn(mostraTabuleiro b)
                 putStrLn("\nVelha!")
             --se houver jogadas possíveis 
             else do
                 -- testa se a última jogada levou a vitória de alguém
                 if((vitoria b) /= ' ') then do
                     putStrLn("Vencedor " ++ (show (vitoria b)));
                     putStrLn(mostraTabuleiro b);
                 -- senão a CPU joga
                 else do
                     jogarSingle(ins b 'O' (melhorJogada b));
        else do 
           putStrLn("\nJogada Invalida!\n");
           jogarSingle tabuleiro  

-------------------------------
--Main function of Single player mode
-- Dependências: jogarSingle
sp = do
  putStrLn "Jogador Vs CPU!\n"
  jogarSingle "012345678"

--------------------------------
---------- Dual Player ---------
--------------------------------

------------------------------
--Main routine of Multiplayer mode
-- Dependências: mostraTabuleiro, vitoria, jogadaPossivel
jogarDual tabuleiro = do
    --apresenta o tabuleiro
    putStrLn (mostraTabuleiro tabuleiro)
    --verifica se há vencedor
    if((vitoria tabuleiro) /= ' ') then do
      --Se houver vencedor o apresenta junto ao seu símbolo (X ou O)
      putStrLn("Vencedor " ++ (show (vitoria tabuleiro)));
    else do
        --atualiza a string de jogadas possíveis da partida
        putStrLn(show (jogadaPossivel tabuleiro)) 
        putStrLn("Player 1: Qual deseja jogar (X)? ")
        pos <- getLine
        --avalia a jogada do jogador e atualiza o tabuleiro se necessário
        let (valido, b) = (jogadaJogador tabuleiro (read pos))
        --se tiver havido modificação será avaliado um True
        if (valido) then do
             --se não houver jogadas possíveis
             if(length (jogadaPossivel tabuleiro) == 1) then do
                 putStrLn(mostraTabuleiro b)
                 putStrLn("\nVelha!")
             --se houver jogadas possíveis 
             else do
                 -- testa se a última jogada levou a vitória de alguém
                 if((vitoria b) /= ' ') then do
                     putStrLn("Vencedor " ++ (show (vitoria b)));
                     putStrLn(mostraTabuleiro b);
                 -- senão player 2 joga
                 
                 else do
                     putStrLn(mostraTabuleiro b)
                     putStrLn(show (jogadaPossivel tabuleiro))
                     putStrLn("Player 2: Qual deseja jogar (O)? ")
                     pos2 <- getLine
                     -- Aplica a mesma verificação feita contra o movimento do player 1 no do player 2 
                     let (valido2, b2) = (jogadaJogador2 b (read pos2))
                     -- Se a jogada do player 2 está ok...
                     if (valido2) then do
                         if(length (jogadaPossivel tabuleiro) == 1) then do
                             putStrLn(mostraTabuleiro b2)
                             putStrLn("\nVelha!")
                         else do
                             --Se após player 2 jogar houver vitória
                             if((vitoria b2) /= ' ') then do
                                 putStrLn("Vencedor " ++ (show (vitoria b2)));
                                 putStrLn(mostraTabuleiro b2);
                             --Senão reinicia uma nova rodada
                             else do
                                 jogarDual b2
                     else do
                         --cria um do-while/loop/goto com Monadas
                         let ttt = do
                             putStrLn("\nJogada Invalida\n");
                             putStrLn(mostraTabuleiro b)
                             putStrLn(show (jogadaPossivel tabuleiro))
                             putStrLn("Player 2: Qual deseja jogar (O)? ")
                             pos2 <- getLine
                             -- Aplica a mesma verificação feita contra o movimento do player 1 no do player 2 
                             let (valido2, b2) = (jogadaJogador2 b (read pos2))
                             -- Se a jogada do player 2 está ok...
                             if (valido2) then do
                                 if(length (jogadaPossivel tabuleiro) == 1) then do
                                     putStrLn(mostraTabuleiro b2)
                                     putStrLn("\nVelha!")
                                 else do
                                 --Se após player 2 jogar houver vitória
                                 if((vitoria b2) /= ' ') then do
                                     putStrLn("Vencedor " ++ (show (vitoria b2)));
                                     putStrLn(mostraTabuleiro b2);
                                 --Senão reinicia uma nova rodada
                                 else do
                                     jogarDual b2
                             else do
                                ttt 
                         ttt
        else do 
           putStrLn("\nJogada Invalida!\n");
           jogarDual tabuleiro  

-------------------------------
--Main function of Single Player.
mp = do
  putStrLn "Jogador Vs Jogador!\n"
  jogarDual "012345678"
