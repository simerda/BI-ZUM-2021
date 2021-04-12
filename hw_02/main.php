<?php

if (\count($argv) > 2) {
    die('Too many arguments.' . PHP_EOL);
}

if (\count($argv) < 2) {
    die('Argument N - number of queens missing.' . PHP_EOL);
}

if (!\ctype_digit($argv[1])) {
    die('Argument must be positive number.' . PHP_EOL);
}

define('NUMBER_OF_QUEENS', (int)$argv[1]);

// initialize chessboard with pseudo-random queen placement
// (each queen is on separate row, but column is selected randomly)

$chessboard = [];
for ($i = 0; $i < NUMBER_OF_QUEENS; $i++) {
    $chessboard[$i] = [];

    for ($j = 0; $j < NUMBER_OF_QUEENS; $j++) {
        $chessboard[$i][] = false;
    }

    /** @noinspection RandomApiMigrationInspection */
    $chessboard[$i][\mt_rand(0, NUMBER_OF_QUEENS - 1)] = true;
}

main($chessboard);

/**
 * @param bool[][] $chessboard
 */
function printChessboard(array $chessboard): void
{
    for ($i = 0; $i < NUMBER_OF_QUEENS; $i++) {

        for ($j = 0; $j < NUMBER_OF_QUEENS; $j++) {

            if ($chessboard[$i][$j]) {
                echo ' ♕ ';
            } else {
                echo ($i + $j) % 2 === 0 ? '███' : '   ';
            }

        }

        echo PHP_EOL;
    }
}


/**
 * @param int $x
 * @param int $y
 *
 * @return bool
 */
function validCoordinates(int $x, int $y): bool
{
    return $x >= 0 && $x < NUMBER_OF_QUEENS && $y >= 0 && $y < NUMBER_OF_QUEENS;
}


/**
 * Scores a candidate for solution.
 * The result is sum of squares of number of queens on a common line (row, column, both diagonals).
 * That means valid solution has the lowest score of 4 * NUMBER_OF_QUEENS.
 *
 * @param bool[][] $chessboard
 * @return int
 */
function score(array $chessboard): int
{
    $score = 0;

    // count per rows
    $row = 0;
    foreach ($chessboard as $line) {
        $lineCount = 0;
        foreach ($line as $queen) {
            if ($queen) {
                $lineCount++;
            }
        }
        $score += $lineCount * $lineCount;
    }

    // count per columns
    for ($x = 0; $x < NUMBER_OF_QUEENS; $x++) {
        $lineCount = 0;
        for ($y = 0; $y < NUMBER_OF_QUEENS; $y++) {
            if ($chessboard[$y][$x]) {
                $lineCount++;
            }
        }
        $score += $lineCount * $lineCount;
    }

    // count per main diagonal
    for ($num = 0; $num < (NUMBER_OF_QUEENS * 2) - 1; $num++) {
        $y = min($num, NUMBER_OF_QUEENS - 1);
        $x = $num < NUMBER_OF_QUEENS ? NUMBER_OF_QUEENS - 1 : $num - NUMBER_OF_QUEENS;
        $lineCount = 0;

        while (validCoordinates($x, $y)) {
            if ($chessboard[$y][$x]) {
                $lineCount++;
            }
            // move to next diagonal coordinate
            $y--;
            $x--;
        }
        $score += $lineCount * $lineCount;
    }

    // count per counter diagonal
    for ($num = 0; $num < (NUMBER_OF_QUEENS * 2) - 1; $num++) {
        $y = min($num, NUMBER_OF_QUEENS - 1);
        $x = $num < NUMBER_OF_QUEENS ? 0 : 2 * NUMBER_OF_QUEENS - $num - 1;
        $lineCount = 0;

        while (validCoordinates($x, $y)) {
            if ($chessboard[$y][$x]) {
                $lineCount++;
            }
            // move to next diagonal coordinate
            $y--;
            $x++;
        }
        $score += $lineCount * $lineCount;
    }

    return $score;
}

/**
 * @param bool[][] $chessboard
 * @return bool[][]
 */
function randomChange(array $chessboard): array
{

    for ($y = 0; $y < NUMBER_OF_QUEENS; $y++) {
        for ($x = 0; $x < NUMBER_OF_QUEENS; $x++) {

            // probability of move is 1/NUMBER_OF_QUEENS for each queen
            /** @noinspection RandomApiMigrationInspection */
            if (!$chessboard[$y][$x] || mt_rand(1, NUMBER_OF_QUEENS) > 3) {
                continue;
            }

            $availablePlaces = [];
            for ($newX = $x - 1; $newX <= $x + 1; $newX++) {
                for ($newY = $y - 1; $newY <= $y + 1; $newY++) {

                    /** @noinspection NotOptimalIfConditionsInspection */
                    if (($newX !== $x || $newY !== $y) && validCoordinates($newX, $newY) && !$chessboard[$newY][$newX]) {
                        $availablePlaces[] = [$newY, $newX];
                    }
                }
            }
            $availablePlacesCount = \count($availablePlaces);

            if($availablePlacesCount <= 0){
                continue;
            }
            // remove queen from current pos
            $chessboard[$y][$x] = false;

            /** @noinspection RandomApiMigrationInspection */
            $selectedPlace = $availablePlaces[mt_rand(0, $availablePlacesCount - 1)];
            $chessboard[$selectedPlace[0]][$selectedPlace[1]] = true;

        }
    }

    return $chessboard;
}


/**
 * @param int $currentScore
 * @param int $candidateScore
 * @param int $temp
 * @return float
 */
function probabilityFunc(int $currentScore, int $candidateScore, int $temp): float
{
    return exp(($currentScore - $candidateScore) / $temp);
}


/**
 * @param bool[][] $chessboard
 */
function main(array $chessboard): void
{
    $targetScore = 4 * NUMBER_OF_QUEENS;
    $temp = 10000000;
    $score = score($chessboard);
    $bestCandidate = $chessboard;
    $bestScore = $score;

    echo "Starting temperature: ${temp}" . PHP_EOL;

    $iterations = 0;
    while ($score > $targetScore && $temp > 0) {
        $iterations++;

        $candidate = randomChange($chessboard);
        $candidateScore = score($candidate);

        if($candidateScore < $score){
            $bestCandidate = $candidate;
            $bestScore = $score;
            $chessboard = $candidate;
            $score = $candidateScore;
        } elseif (probabilityFunc($score, $candidateScore, $temp) >= mt_rand() / mt_getrandmax()) {
            $chessboard = $candidate;
            $score = $candidateScore;
        }

        //$temp -= 10;
        $temp = $temp / 1.00001 - 1;
    }

    if ($score <= $targetScore) {
        printChessboard($chessboard);
        echo "Solution found in ${iterations} iterations." . PHP_EOL;
        echo "Final temperature: ${temp}" . PHP_EOL;

    } else {
        echo "Could not find the solution. Tried ${iterations} iterations." . PHP_EOL;
        echo "Our best solution is with score ${bestScore}: " . PHP_EOL;
        printChessboard($bestCandidate);
    }
}







