# cpp-coso

[![CPP-COSO - DEFAULT](https://github.com/MGuillaumeF/cpp-coso/actions/workflows/default.yml/badge.svg?branch=main)](https://github.com/MGuillaumeF/cpp-coso/actions/workflows/default.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=MGuillaumeF_cpp-coso&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=MGuillaumeF_cpp-coso)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=MGuillaumeF_cpp-coso&metric=coverage)](https://sonarcloud.io/summary/new_code?id=MGuillaumeF_cpp-coso)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=MGuillaumeF_cpp-coso&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=MGuillaumeF_cpp-coso)
[![wakatime](https://wakatime.com/badge/user/9f76e922-98e1-4ef0-b832-f1f6bb21d4c3/project/72ac7efd-84ae-45f5-9050-06aaae1d7d62.svg)](https://wakatime.com/badge/user/9f76e922-98e1-4ef0-b832-f1f6bb21d4c3/project/72ac7efd-84ae-45f5-9050-06aaae1d7d62)

## description

This application convert cpp result report of lint tools to sonarqube generic data issue report

## conversions available

- gcc/g++ warning text logs to sonarqube generic data issues
- cppcheck XML reports to sonarqube generic data issues
- clang-tidy plain text reports to sonarqube generic data issues
- boost test XML reports to sonarqube generic test reports

## how to use

```sh
# convert gcc/g++ warnings plain text report to sonarqube generic data issue report
cpp-coso gcc-warning ./path/to/reports/gcc_warning_source_report.txt ./path/to/reports/gcc-warning-sonarqube-report.json

# convert clang tidy plain text report to sonarqube generic data issue report
cpp-coso clang-tidy ./path/to/reports/clang_tidy_source_report.txt ./path/to/reports/clang-tidy-sonarqube-report.json

# convert cppcheck xml report to sonarqube generic data issue report
cpp-coso cppcheck ./path/to/reports/cppcheck_source_report.xml ./path/to/reports/cppcheck-sonarqube-report.json

# convert boost tests xml reports to sonarqube generic tests results
cpp-coso boost-test boost-test-log-report.xml boost-test-results-report.xml boost-test-sonarqube-report.json
```

## use in github actions (Linux)

```yaml
- name: Install dependencies
  run: sudo apt-get install -y clang-tidy cppcheck

- name: Lint Cpp Check
  run: cppcheck --enable=all --inconclusive --language=c++ --std=c++20 --xml --output-file=./path/to/reports/cppcheck_report.xml ./root/to/project

- name: Lint Clang-Tidy
  run: clang-tidy -checks='*' -header-filter='src/.*' -p ./bin > ./path/to/reports/clang_tidy_report.txt

- name: Download cpp-coso
  uses: wei/wget@v1
  with:
    args: -O cpp-coso-${{env.CPP_COSO_VERSION}}-Linux.deb https://mguillaumef.github.io/cpp-coso/delivery/${{env.CPP_COSO_VERSION}}/cpp-coso-${{env.CPP_COSO_VERSION}}-Linux.deb

- name: Install cpp-coso
  run: sudo dpkg -i cpp-coso-${{env.CPP_COSO_VERSION}}-Linux.deb

- name: Convert GCC warnings to sonarqube format
  run: /usr/cpp-coso/cpp-coso gcc-warning ./path/to/reports/gcc_warning_report.txt ./path/to/reports/gcc-warning-sonarqube-report.json

- name: Convert Lint Clang-Tidy to sonarqube format
  run: /usr/cpp-coso/cpp-coso clang-tidy ./path/to/reports/clang_tidy_report.txt ./path/to/reports/clang-tidy-sonarqube-report.json

- name: Convert Lint Cpp Check to sonarqube format
  run: /usr/cpp-coso/cpp-coso cppcheck ./path/to/reports/cppcheck_report.xml ./path/to/reports/cppcheck-sonarqube-report.json

- name: Convert Boost Tests to sonarqube format
  run: /usr/cpp-coso/cpp-coso boost-test boost-test-log-report.xml boost-test-results-report.xml boost-test-sonarqube-report.json
```

## projects using package

- [hangman-game](https://github.com/MGuillaumeF/hangman-game)
