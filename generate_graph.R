#!/usr/bin/Rscript

args <- commandArgs(trailingOnly = TRUE)

data <- read.csv(args[1], sep=";")

svg(args[2], width=14, height=10)
par(mfrow=c(1,2))

boxplot(data, ylab = "Time in millisecond", xlab = "Algorithme")
ts.plot(data, col=c("orange", "red", "blue", "purple"), xlab = "replicate", ylab = "Time in millisecond")
legend("topright", col = c("orange", "red", "blue", "purple"), legend = colnames(data), lwd=1, lty=c(1,1))

tmp <- dev.off()
