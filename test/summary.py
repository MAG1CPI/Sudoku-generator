import os
import subprocess
import re

DIR = "C:/CODE/Sudoku-generator/test/cov"

files = [os.path.join(DIR, file) for file in os.listdir(DIR) if re.match(r".+\.cov$", file)]

command = ["OpenCppCoverage", "--export_type=html:coverage_result"]
for coverage_file in files:
    command.extend(["--input_coverage", coverage_file])

subprocess.call(command)