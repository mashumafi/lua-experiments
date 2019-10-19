local count = 1000
local x = os.clock()
for i=1,count do
    avg, sum = average(10, 20, 30, 40, 50)
end
print(string.format("average: %.2f\n", os.clock() - x))

x = os.clock()
for i=1,count do
    avg, sum = ez_average(10, 20, 30, 40, 50)
end
print(string.format("ez_average: %.2f\n", os.clock() - x))