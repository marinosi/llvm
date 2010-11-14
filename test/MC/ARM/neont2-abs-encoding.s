@ RUN: llvm-mc -mcpu=cortex-a8 -triple thumb-unknown-unkown -show-encoding < %s | FileCheck %s

.code 16

@ CHECK: vabs.s8	d16, d16                @ encoding: [0x20,0x03,0xf1,0xff]
	vabs.s8	d16, d16
@ CHECK: vabs.s16	d16, d16        @ encoding: [0x20,0x03,0xf5,0xff]
	vabs.s16	d16, d16
@ CHECK: vabs.s32	d16, d16        @ encoding: [0x20,0x03,0xf9,0xff]
	vabs.s32	d16, d16
@ CHECK: vabs.f32	d16, d16        @ encoding: [0x20,0x07,0xf9,0xff]
	vabs.f32	d16, d16
@ CHECK: vabs.s8	q8, q8                  @ encoding: [0x60,0x03,0xf1,0xff]
	vabs.s8	q8, q8
@ CHECK: vabs.s16	q8, q8          @ encoding: [0x60,0x03,0xf5,0xff]
	vabs.s16	q8, q8
@ CHECK: vabs.s32	q8, q8          @ encoding: [0x60,0x03,0xf9,0xff]
	vabs.s32	q8, q8
@ CHECK: vabs.f32	q8, q8          @ encoding: [0x60,0x07,0xf9,0xff]
	vabs.f32	q8, q8

@ CHECK: vqabs.s8	d16, d16        @ encoding: [0x20,0x07,0xf0,0xff]
	vqabs.s8	d16, d16
@ CHECK: vqabs.s16	d16, d16        @ encoding: [0x20,0x07,0xf4,0xff]
	vqabs.s16	d16, d16
@ CHECK: vqabs.s32	d16, d16        @ encoding: [0x20,0x07,0xf8,0xff]
	vqabs.s32	d16, d16
@ CHECK: vqabs.s8	q8, q8          @ encoding: [0x60,0x07,0xf0,0xff]
	vqabs.s8	q8, q8
@ CHECK: vqabs.s16	q8, q8          @ encoding: [0x60,0x07,0xf4,0xff]
	vqabs.s16	q8, q8
@ CHECK: vqabs.s32	q8, q8          @ encoding: [0x60,0x07,0xf8,0xff]
	vqabs.s32	q8, q8