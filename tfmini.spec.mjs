import {TFMiniParser, checksum} from "./tfmini.mjs";
import chai from "chai";

const {expect} = chai;

describe("TFMini class", () => {
    let tfmini;
    let tfminiFunc;
    let goodDistanceSequence;
    let goodConfigSequence;
    let distance = -1;
    let config;
    beforeEach(() => {
        tfminiFunc = TFMiniParser({
            distance: dist => {distance = dist;},
            config: conf => {config = conf;}
        });
        goodDistanceSequence = [0x59,0x59,211,30,0,0,0,0,checksum(89,89,211,30)];
        goodConfigSequence = [0x42,0x57,0x2,0x1,0x0,0x0,0x1,0x2];
        distance = -1;
        config = [];
    });
    
    describe("receives a valid distance packet of 7891", () => {
        beforeEach(async () => {
            await tfminiFunc(goodDistanceSequence);
        });

        it("emits a distance event", () => {
            expect(distance).to.equal(7891);
        });
    });

    describe("receives a valid distance packet in the middle of garbage", () => {
        beforeEach(async () => {
            await tfminiFunc([44,100,44,0]);
            await tfminiFunc(goodDistanceSequence);
        });

        it("emits a distance event", () => {
            expect(distance).to.equal(7891);
        });
    });

    describe("receives a valid distance packet in the middle of garbage", () => {
        beforeEach(async () => {
            tfminiFunc([44,89,100,44,0]);
            tfminiFunc(goodDistanceSequence);
        });

        it("emits a distance event", () => {
            expect(distance).to.equal(7891);
        });
    });

    describe("receives a valid config packet", () => {
        beforeEach(async () => {
            await tfminiFunc(goodConfigSequence);
        });

        it("emits a distance event", () => {
            expect(config).to.deep.equal([2,1,0,0,1,2]);
        });
    });

    describe("receives a valid config packet in the middle of garbage", () => {
        beforeEach(async () => {
            await tfminiFunc([44,100,44,0]);
            await tfminiFunc(goodConfigSequence);
        });

        it("emits a distance event", () => {
            expect(config).to.deep.equal([2,1,0,0,1,2]);
        });
    });

    describe("receives a valid config packet in the middle of garbage", () => {
        beforeEach(async () => {
            tfminiFunc([44,42,100,44,0]);
            tfminiFunc(goodConfigSequence);
        });

        it("emits a distance event", () => {
            expect(config).to.deep.equal([2,1,0,0,1,2]);
        });
    });

    describe("receives an invalid range packet", () => {
        beforeEach(async () => {
            tfminiFunc([89,89,211,30,0,0,0,0,0]);
        });

        describe("receives a valid range packet", () => {
            beforeEach(async () => {
                tfminiFunc(goodConfigSequence);
            });
    
            it("emits a distance event", () => {
                expect(config).to.deep.equal([2,1,0,0,1,2]);
            });
        });
    });
});

