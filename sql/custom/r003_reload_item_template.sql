/*
SQLyog Ultimate
MySQL - 10.1.26-MariaDB-0+deb9u1
*********************************************************************
*/
/*!40101 SET NAMES utf8 */;

/* create table `command` (
	`name` varchar (150),
	`security` tinyint (3),
	`help` text
); */

delete from `command` where `name`='reload item_template';
insert into `command` (`name`, `security`, `help`) values('reload item_template','3','Syntax: .reload item_template');
