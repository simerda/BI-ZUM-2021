
  (define	(problem jug-1)
	(:domain jug)
	(:objects
		j3 j5 jfinal	- jug
		)
	(:init
	    (= (capacity j3) 3) (= (volume j3) 0)
	    (= (capacity j5) 5) (= (volume j5) 0)
	    (= (capacity jfinal) 100) (= (volume jfinal) 0)
	)
	(:goal
	    (= (volume jfinal) 4)
	)
)