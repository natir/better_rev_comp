#!/usr/bin/Rscript

args <- commandArgs(trailingOnly = TRUE)

data <- read.csv(args[1], sep=";")

png(args[2], width=760, height=480, units="px")
par(mfrow=c(1,2))

boxplot(data, ylab = "Time in millisecond", xlab = "Algorithme")
ts.plot(data, col=c("red", "blue"), xlab = "replicate", ylab = "Time in millisecond")
legend("topright", col = c("red", "blue"), legend = colnames(data), lwd=1, lty=c(1,1))

tmp <- dev.off()
