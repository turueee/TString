file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h
add_executable(${application} ${srcs} ${hdrs}) #Создаем проект с именем из переменной ${vector}, в него добавляются файлы из переменных ${srcs} и ${hdrs}
target_link_libraries(${application} ${stringlib}) #Подключаем к проекту с именем ${vector} библиотеку с именем ${vectorlib}
target_link_libraries(${application} ${errorlib})

#add_library(${MyLib1} STATIC ${srcs} ${hdrs}) #Создаем статическую библиотеку с именем из переменной ${MyLib1}, объявленной в родительском CMake файле (локальные переменные переносятся в наследников), в неё добавляются файлы из переменных ${srcs} и ${hdrs}


