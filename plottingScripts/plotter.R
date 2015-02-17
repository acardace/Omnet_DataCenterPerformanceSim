require(ggplot2)
args <- commandArgs(trailingOnly = TRUE)
xfile <- args[1]
outfile <- args[2]
xlabel <-args[3]
ylabel <-args[4]
heading <- args[5]

file <- read.csv(file=xfile,head=TRUE,sep=",")
xrange <-range(file$X)
yrange <-range(file$Y)
#png(outfile, width=1000, height=800)
#plot(xrange, yrange, main=heading, xlab=xlabel, ylab=ylabel, type="n")
#par(pch=23, col="red")
#lines(file$X,file$Y,type="b")
qp <- qplot(file$X,file$Y, alpha=1, geom="smooth", xlim=xrange, ylim=yrange, xlab=xlabel, ylab=ylabel, main=heading) + theme(legend.position="none")
ggsave(qp, file=outfile)
