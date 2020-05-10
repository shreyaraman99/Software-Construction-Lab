By running
$ make clean check
I get the following results:

time ./srt 1-test.ppm >1-test.ppm.tmp

real 0m47.810s
user 0m47.798s
sys  0m0.005s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real 0m24.705s
user 0m49.110s
sys  0m0.002s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real 0m12.716s
user 0m50.394s
sys  0m0.000s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real 0m8.610s
user 1m5.129s
sys  0m0.003s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done


Looking at this, I see that the real time decreases with increasing number of threads. The real time is approximately the user time divided by the number of threads. As the number of threads 
increase, there is a small increase in the user time, which occurs because more threads are being created.

The issue I had was moving variables around so when I ran the code, a lot of variables were undefined.
