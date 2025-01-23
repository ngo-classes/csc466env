# CSC466 Cluster

A template to support development of containerization learning materials

## Notes:

### Warning

- If you clone into a Windows environment, makes sure that your git is set to keep `LF`:

~~~
git config --global core.autocrlf false
git clone https://github.com/class-master/csc466env
~~~

### Building the images

- You should build the images in the following order:
~~~
docker compose build base --no-cache
docker compose build head --no-cache
~~~

### Launching the cluster

- You should launch in the following order:
~~~
docker compose up -d head
docker compose up -d compute01
docker compose up -d compute02
~~~

### Test

- Access the VSCode server via http://127.0.0.1:18088/
    - Password is **goldenrams** 
- Open a terminal
- Test the environment as follows:

~~~
mpicc -o hello mpi_hello_world.c 
mpirun --host compute01:2,compute02:2 -np 4 ./hello
~~~



After this is done, update `.gitignore` so that temporary files generated in home are not included. 

### Build mkdocs server (for instructor)

`mkdocs serve --dev-addr=0.0.0.0:8000` to support external view of mkdocs
