///////////////////////////////////////////////////////////
// MerchantSpeech.inc
//
// Merchant speech.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
// Keywords:
//	buy
//	sell
//	restock
//	show stock
//	show bought
//	show spare
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// GLOBAL CODE
///////////////////////////////////////////////////////////
EnableEvents(EVID_MERCHANT_BOUGHT + EVID_MERCHANT_SOLD);

///////////////////////////////////////////////////////////
// Purpose: Test to see if I should process speech or not.
// Params:  ev		Event object.
//						ev.type		Event type.
//						ev.source	Source of event.
//						ev.text		Text of event.
//						ev.item		Item associated w/ event.
//						ev.amount	Amount associated w/ event.
// Returns: 0		No, do not process speech.
//			1		Yes, talk to me baby!
///////////////////////////////////////////////////////////
function SpeechTest(byref ev)
	if (ev.source.murderer)
		Say("Begone villain! Guards! Guards! He is pointing a weapon at me!");
		return 0;
	endif

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Custom speech processing here.
// Params:  ev		Event object.
//						ev.type		Event type.
//						ev.source	Source of event.
//						ev.text		Text of event.
//						ev.item		Item associated w/ event.
//						ev.amount	Amount associated w/ event.
// Returns: 0		Do not do default processing.
//			1		Continue with default processing.
///////////////////////////////////////////////////////////
function Speech(byref ev)
	case (ev.type)
		EVID_SPEECH:
			var text := lower(ev.text);

			if (text["buy"])
				if (ev.source.criminal)
					Say("Filth like ye shall pay extra!");
				endif

				SetPrices(InvStock, ev.source, 1);
				SetPrices(InvBought, ev.source, 1);
				SendBuyWindow(ev.source, InvStock, me, InvBought);

			elseif (text["sell"])
				if (ev.source.criminal)
					Say("I refuse to pay a fair price to thy kind!");
				endif

				SetPrices(ev.source.backpack, ev.source);
				SendSellWindow(ev.source, me, InvStock, InvBought, InvSpare);

			elseif (text["restock"])
				if (ev.source.cmdlevel)
					RestockInventory();
					Say("My inventory has been replenished, Oh Great One.");
				endif

			elseif (text["show stock"])
				if (ev.source.cmdlevel)
					SendOpenSpecialContainer(ev.source, InvStock);
				endif

			elseif (text["show bought"])
				if (ev.source.cmdlevel)
					SendOpenSpecialContainer(ev.source, InvBought);
				endif

			elseif (text["show spare"])
				if (ev.source.cmdlevel)
					SendOpenSpecialContainer(ev.source, InvSpare);
				endif
			endif

		EVID_MERCHANT_BOUGHT:


		EVID_MERCHANT_SOLD:


	endcase

	return 1;
endfunction