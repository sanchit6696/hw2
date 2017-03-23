CC=gcc-6
FLAGS= -fopenmp 
EXECS= omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 gsd2D_omp jacobi2D_omp gsd jacobi

all: ${EXECS}

omp_solved2: omp_solved2.c
	${CC} ${FLAGS} omp_solved2.c -o omp_solved2

omp_solved3: omp_solved3.c
	${CC} ${FLAGS} omp_solved3.c -o omp_solved3

omp_solved4: omp_solved4.c
	${CC} ${FLAGS} omp_solved4.c -o omp_solved4

omp_solved5: omp_solved5.c
	${CC} ${FLAGS} omp_solved5.c -o omp_solved5

omp_solved6: omp_solved6.c
	${CC} ${FLAGS} omp_solved6.c -o omp_solved6

gsd2D_omp: gsd2D_omp.c
	${CC} ${FLAGS} gsd2D_omp.c -o gsd2D_omp

jacobi2D_omp: jacobi2D_omp.c
	${CC} ${FLAGS} jacobi2D_omp.c -o jacobi2D_omp

gsd: gsd.c
	${CC} gsd.c -o gsd

jacobi: jacobi.c
	${CC} jacobi.c -o jacobi


clean:
	rm -f ${EXECS}
