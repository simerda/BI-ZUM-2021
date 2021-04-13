(define	(problem assembler-1)
	(:domain assembler)
	(:objects
		reg1 reg2		                    - register
		i0 i1 i2 i3 i4 i5 i6 i7 i8 i9 		- index
	    mem                                 - memory
	    a b c d e f g h i j garbage         - data
		)
	(:init
	    (stores mem i0 j) (stores mem i1 i) (stores mem i2 h) (stores mem i3 g) (stores mem i4 f) (stores mem i5 e) (stores mem i6 d) (stores mem i7 c) (stores mem i8 b) (stores mem i9 a)
	    (caches reg1 garbage) (caches reg2 garbage)
	)
	(:goal
	    (and
	    (stores mem i0 a) (stores mem i1 b) (stores mem i2 c) (stores mem i3 d) (stores mem i4 e) (stores mem i5 f) (stores mem i6 g) (stores mem i7 h) (stores mem i8 i) (stores mem i9 j)
	    )
	)
)