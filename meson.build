project(
  'cpp-boilerplate',
  'cpp',
  version : '0.0.1',
  default_options : ['cpp_std=c++17'],
)

compiler = meson.get_compiler('cpp')

thread = dependency('threads')
boost = dependency('boost')
gtest = dependency('gtest', required : false)

crow_include = include_directories('../crow/include')

exe = executable(
  'cpp-url-shortener',
  'main.cpp',
  'src/crow_server.cpp',
  'src/memory_database.cpp',
  'src/shortener.cpp',
  include_directories: [
    crow_include,
  ],
  dependencies : [
    thread,
    boost,
  ],
  link_args: [
    '-lboost_system',
  ],
)

test_exe = executable(
  'tests',
  'test/test_main.cpp',
  'test/test.cpp',
  dependencies : [
    gtest,
  ]
)
test('tests', test_exe)
