---

---

# Profiling
## Scientific Computing II
### Konrad Lorenz University

---

#### `cProfile`
`cProfile` can be used in a single name. Namely,
```python
import cProfile
cProfile.run("print('Hello profiling!')")
```
and we get the statistics of all functions run. These results can be saved in a file.
```python

cProfile.run("print('Hello profiling!')", 'profiler')
```
and we call it using `pstats`
```python
import pstats
a = pstats.Stats('profiler')
a.print_stats()
```
---

#### `cProfile`

`cProfile` can also be invoked as a module to profile a given script (or module). The syntax is as follows.
```bash
python -m cProfile [-o output_file] [-s sort_order] (-m module | myscript.py)
```
Let us see an example. Run
```bash
python -m cProfile examples/factorial.py
```
---

#### `kernprof`
You'd probably need to install its dependency, `line-profiler`, using pip
```bash
pip install line-profiler
```
You can find `kernprof` in `examples/` or here: https://raw.githubusercontent.com/pyutils/line_profiler/main/kernprof.py

To use it, the objective functions should have the `@profile` flag (see files in `examples/`).
```bash
kernprof -l examples/Example1.py
```
The results are written in a binary file. Flag `-v/--view` presents it
immediately. Otherwise, you can read the binary using `line_profiler` 
```python
python -m line_profiler examples/Example1.py.lprof
```
Let us study the other scripts in `examples/`.
