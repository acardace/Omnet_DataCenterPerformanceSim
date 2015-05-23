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
qp <- qplot(file$X,file$Y, alpha=1, geom="smooth", xlim=xrange, ylim=yrange, xlab=xlabel, ylab=ylabel, main=heading) + theme(legend.position="none")
ggsave(qp, device=svg,file=outfile)
