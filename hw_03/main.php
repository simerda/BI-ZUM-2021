<?php

main();

/**
 * @return string
 */
function input(): string
{
    return trim(fgets(STDIN));
}

/**
 * @return string[][]
 */
function readGraph(): array
{
    $neighbours = [];
    echo 'Please define names for your vertices (delimited by newline). Reading will stop after empty input.' . PHP_EOL;

    $vertexRegex = '/^[a-z][a-z0-9]*$/';

    while(!empty($line = input())){

        if(preg_match($vertexRegex, $line) !== 1){
            die('Vertex name must consist only of lowercase characters and digits. '.
                'Vertex name must not begin with digit.' . PHP_EOL);
        }

        if(\array_key_exists($line, $neighbours)){
            echo 'Already exist. Skipping...' . PHP_EOL;
            continue;
        }

        $neighbours[$line] = [];
    }

    if(empty($neighbours)){
        die('You have to enter some vertices' . PHP_EOL);
    }


    echo 'Please enter comma separated names of vertices that are adjacent to given vertex.' . PHP_EOL;
    $neighbourRegex = '/^(([a-z][a-z0-9]*), ?)*([a-z][a-z0-9]*)$/';
    foreach ($neighbours as $vertex => $_){

        echo $vertex . ': ';

        $line = input();
        if(preg_match($neighbourRegex, $line) !== 1){
            die('Format is not valid.' . PHP_EOL);
        }

        $selected = \explode(',', str_replace(' ', '', $line));

        foreach($selected as $v){
            if(! array_key_exists($v, $neighbours)){
                die("Vertex \"${v}\" not found." . PHP_EOL);
            }
            // we don't want reflexive relation
            if($v !== $vertex){
                $neighbours[$vertex][] = $v;
            }
        }
    }

    return $neighbours;
}

/**
 * @param string[] $vertices
 * @return string[][]
 */
function readAgents(array $vertices): array
{
    echo 'Please define names for your agents (delimited by newline). '.
        'Reading will stop after empty input or after (vertices-count - 1).' . PHP_EOL;

    $agents = [];
    $vertexCount = \count($vertices);
    $agentRegex = '/^[a-z][a-z0-9]*$/';
    for($i = 0; $i < $vertexCount && !empty($agent = input()); $i++){

        if(\preg_match($agentRegex, $agent) !== 1){
            die('Agent name must consist only of lowercase characters and digits. '.
                'Agent name must not begin with digit.' . PHP_EOL);
        }

        if(array_key_exists($agent, $agents)){
            echo 'Agent with same name already define. Skipping...' . PHP_EOL;
            $i--;
            continue;
        }
        $agents[$agent] = null;

    }

    return $agents;
}


function readAgentPlaces(array $agents, array $vertices): array
{
    foreach($agents as $agent => $_){

        echo "Enter vertex for agent \"${agent}\": ";
        $vertex = input();

        if(! in_array($vertex, $vertices, true)){
            die('Vertex not found' . PHP_EOL);
        }

        if(in_array($vertex, $agents, true)){
            die('Vertex already occupied' . PHP_EOL);
        }

        $agents[$agent] = $vertex;
    }

    return $agents;
}


function generateProblemDefinition(array $neighbours, array $agents, array $agentsStart, array $agentsEnd): string
{
    $agentsStr = \implode(' ', $agents);
    $verticesStr = \implode(' ', \array_keys($neighbours));
    $emptyVertices = \array_diff(\array_keys($neighbours), \array_values($agentsStart));
    $problem = '';
    // header
    $problem .= "(define\t(problem mapf-problem)" . PHP_EOL
	."(:domain mapf)" . PHP_EOL
	."(:objects " . PHP_EOL
    ."${agentsStr}\t - agent" . PHP_EOL
    ."${verticesStr}\t - vertex" . PHP_EOL . ')' . PHP_EOL
	."(:init" . PHP_EOL;
    foreach ($neighbours as $fromVertex => $vertices){
        foreach($vertices as $toVertex){
            $problem .= "(edge ${fromVertex} ${toVertex}) ";
        }
    }
    $problem .= PHP_EOL;

    foreach ($emptyVertices as $vertex){
        $problem .= "(empty ${vertex}) ";
    }
    $problem .= PHP_EOL;

    foreach ($agentsStart as $agent => $vertex){
        $problem .= "(at ${agent} ${vertex}) ";
    }
    $problem .= PHP_EOL . ')' . PHP_EOL
    ."(:goal" . PHP_EOL . '(and ';

    foreach ($agentsEnd as $agent => $vertex){
        $problem .= "(at ${agent} ${vertex}) ";
    }
    $problem .= ')' . PHP_EOL . ')' . PHP_EOL . ')' . PHP_EOL;

    return $problem;
}


function main(): void
{
    $neighbours = readGraph();
    $agents = readAgents(\array_keys($neighbours));

    echo 'Please enter starting positions for your agents.' . PHP_EOL;
    $agentsStart = readAgentPlaces($agents, \array_keys($neighbours));
    echo 'Please enter target positions for your agents.' . PHP_EOL;
    $agentsEnd = readAgentPlaces($agents, \array_keys($neighbours));

    $problem = generateProblemDefinition($neighbours, \array_keys($agents), $agentsStart, $agentsEnd);
    $path = 'mapf-problem.pddl';
    if(file_put_contents($path, $problem)){
        echo "Problem definition stored to file ${path}" . PHP_EOL;
    }else{
        echo "Failed to write data." . PHP_EOL;
    }
}










