[![CMakeTest](https://github.com/GlebNM/TicTacToe/actions/workflows/cmake_tests.yml/badge.svg)](https://github.com/GlebNM/TicTacToe/actions/workflows/cmake_tests.yml)
[![Code Grade](https://api.codiga.io/project/32613/status/svg)](https://www.codiga.io)
[![Code Grade](https://api.codiga.io/project/32613/score/svg)](https://www.codiga.io)
[![codecov](https://codecov.io/gh/GlebNM/TicTacToe/branch/dev/graph/badge.svg?token=9K3W1ZIT96)](https://codecov.io/gh/GlebNM/TicTacToe)
# Ultimate Tic-Tac-Toe

## О проекте
Основной задачей является написание сильного искусственного интеллекта для игры в особую версию 
крестиков-ноликов. Будет реализовано несколько ботов, имеющих общий базовый класс.
Предполагается, что самым сильным из них будет основанный на MCTS(Monte-Carlo Tree Search).

Будет добавлена возможность игры между людьми, человеком и компьютером, и двумя ботами.
В случае игры между ботами будет пересчитываться их рейтинг в зависимости от результатов игры.

## Правила
Об игре и правилах можно прочитать [здесь](https://en.wikipedia.org/wiki/Ultimate_tic-tac-toe).
Мы рассматриваем вариант правил, при котором нельзя ходить в большую клетку, если она выиграна
(в противном случае крестики имеют несложную выигрышную стратегию). И если на доске
больше нет возможных ходов и нет линии из больших клеток,
то победитель определяется по общему числу выигранных больших клеток
(при равенстве объявляется ничья).

## Запуск
```shell
git clone https://github.com/GlebNM/TicTacToe.git
cd TicTacToe
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING=OFF
make
cd ../bin
chmod +x main
./main
```
