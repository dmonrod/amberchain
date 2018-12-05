#!/bin/bash

amberpid=`ps -e | grep amber | grep -Eo '[0-9]{4,5}'`

logfile="$HOME/cron_logs/amberchaind.log"

if [ -z "$amberpid" ]
then
    timestamp="`date "+%Y-%m-%d %H:%M:%S"`"
    log="[ $timestamp ] amberchaind is down."
    echo $log >> $logfile
    timestamp="`date "+%Y-%m-%d %H:%M:%S"`"
    log="[ $timestamp ] running restart_chain.sh"
    echo $log >> $logfile
    sudo $HOME/amberchain/restart_chain.sh >> $logfile
    timestamp="`date "+%Y-%m-%d %H:%M:%S"`"
    log="[ $timestamp ] restart_chain.sh ran successfully"
    echo $log >> $logfile
else
    timestamp="`date "+%Y-%m-%d %H:%M:%S"`"
    log="[ $timestamp ] amberchaind pid is: $amberpid"
    echo $log >> $logfile
fi