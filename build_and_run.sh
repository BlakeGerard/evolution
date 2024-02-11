src="src/evo_utils.c src/evo_actor.c src/evo_actorarray.c src/evo_environment_array.c src/evo_operators.c src/evo.c"
inc="src/evo_utils.h src/evo_actor.h src/evo_actorarray.h src/evo_environment_array.h src/evo_operators.h"
lib="-lm"
flags="-O3"

gcc $inc $src $flags $lib -o evo
./evo
