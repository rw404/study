error = MPI_Init(&argc, &argv);
if (error != MPI_SUCCESS) {
  fprintf(stderr, "MPI_Init error\n");
  return 1;
}
